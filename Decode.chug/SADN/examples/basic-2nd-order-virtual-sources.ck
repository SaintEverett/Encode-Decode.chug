if(dac.channels() < 9) me.exit(); // not enough channels?
int n;
if(me.args()) me.arg(0) => Std.atoi => n; // how many sources?

float speaks[9][2];
for(int i; i < speaks.size(); i++)
{
   i*(360.0/8.0) => speaks[i][0]; // ring of 8 dividing 360 degrees
}

Encode2 enc[n];
NRev rev[n];
SinOsc obj[n];
Envelope env[n];
SAD2 deco(speaks); // constructor!

fun void randomPlacement(Encode2 p)
{
    Math.random2f(0.0, 360.0) => float randomAzi;
    while(true)
    {
        randomAzi+Math.random2f(0,4.5) => randomAzi;
        if(randomAzi > 360) randomAzi-360.0 => randomAzi;
        p.pos(randomAzi,0);
        <<< randomAzi >>>;
        10::ms => now;
    }
}

fun void randomPitch(SinOsc s, Envelope e)
{
    22.0 => float base;
    while(true)
    {
        Math.random2(1,5) => float random;
        Math.random2f(0.125,2.5) * random => random;
        base * random => s.freq;
        //e.duration $ int => int timmy; // how to cast dur to int?
        35000 => int timmy;
        for(int i; i < 6; i++)
        {
            e.keyOn();
            e.duration() => now;
            s.freq()*1.25 => s.freq;
            for(int i; i < 6; i++)
            {
                s.freq()*Math.random2f(0.125, 2.4) => s.freq;
                (timmy/(Math.random2f(10.0,1000.0)))::ms => now;
            }
            Math.random2f(4.5,450)::ms => now;
            e.keyOff();
            e.duration() => now;
            e.keyOn();
            (s.freq()/random)*0.8 => s.freq;
            for(int i; i < 6; i++)
            {
                s.freq()*Math.random2f(0.125, 2.4) => s.freq;
                (timmy/(6.0))::ms => now;
            }
            e.duration() => now;
            Math.random2f(4.5,450)::ms => now;
            s.freq()*0.5 => s.freq;
            e.keyOff();
            e.duration();
        }
        5000::ms => now;
    }
}


for(int i; i < n; i++)
{
    enc[i].gain(1.0/n); // scale
    obj[i].freq(Math.random2f(34.0,1652.0));
    obj[i] => env[i] => rev[i] => enc[i] => deco => blackhole;
    rev[i].mix(0.0125);
    Math.random2f(0.125,72.5)::ms => env[i].duration;
    spork ~ randomPlacement(enc[i]);
    spork ~ randomPitch(obj[i], env[i]);
}

for(int i; i < deco.channels(); i++)
{
    deco.chan(i) => dac.chan(i);
}

while(true)
{
    100::ms => now;
}

