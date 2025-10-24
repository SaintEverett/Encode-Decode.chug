// treeOsc by everett m. carpenter

global Event rando;

Encode2 enc;
SAD2 deco;
SinOsc trunk;
int branchCollection;

Math.random2f(56.0,287.0) => float root => trunk.freq; 

[1.0, 1.125, 1.25, 1.333, 1.5, 1.666, 1.875, 2.0] @=> float justIn[];

float speaks[9][2];
for(int i; i < speaks.size(); i++)
{
   i*(360.0/8.0) => speaks[i][0]; // ring of 8 dividing 360 degrees
}

deco.placement(speaks);

trunk => enc => deco => dac;

fun void loopEnv(Envelope l)
{
    while(true)
    {
        l.keyOn();
        l.duration() => now;
        l.keyOff();
        l.duration()+500::ms => now;
    }
}

fun void branch(float degree,dur life)
{
    Encode2 enco;
    Encode2 leaveEnco[8];
    SinOsc branch(degree);
    SinOsc leaves[8];
    Gain sum;
    Envelope branchEnv;
    Envelope leaveEnv[8];
    Math.random2f(0.0, 360.0) => float position;
    enco.pos(position, 0.0);
    life => branchEnv.duration;
    branch.gain(0.25/10.0);
    branch => branchEnv => sum;
    branchCollection+1 => branchCollection;
    for(int i; i < leaves.size(); i++)
    {
        leaves[i].gain(0.75/10.0);
        leaves[i].freq(degree * justIn[Math.random2(0,justIn.size()-1)] * Math.random2(1,6));
        leaveEnv[i].target(1.0);
        leaves[i] => leaveEnv[i] => leaveEnco[i];
        leaveEnco[i].pos(position+(Math.random2f(-1.0,1.0)*Math.random2f(5.0,45.0)),0.0);
        life*(Math.random2f(0.125,0.85)) => leaveEnv[i].duration;
    }
    sum => enco => deco;

    branchEnv.keyOn();      // begin singing
    branchEnv.duration()/2 => now;

    Math.random2f(1000,5000)::ms => now; // wait for leaves to bloom
    for(int i; i < leaveEnv.size(); i++)
    {
        spork ~ loopEnv(leaveEnv[i]); // one at a time
        Math.random2f(285.0, 980.0)::ms => now;
    }

    Math.random2f(1.0,2.5)*life => now; // wait and breath
    
    for(int i; i < leaveEnv.size(); i++)
    {
        leaveEnv[i].target(0.0); // go down
    }
    
    leaveEnv[Math.random2(0,leaveEnv.size()-1)].duration()+400::ms => now; // wait for leaves to be down
    branchEnv.keyOff(); // turn off main branch
    branchEnv.duration() => now;

    branchCollection-1 => branchCollection; // set how many active branches
}

spork ~ branch(justIn[3]*root, 10::second);
while(true)
{
    cherr <= branchCollection <= IO.newline();
    4::second => now;
}