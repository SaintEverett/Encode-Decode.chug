Encode1 enc;
SAD1 sad;
Impulse imp;

SinOsc sin(452.0);
imp.gain(0.5);
enc.gain(1.0);
WvOut SpeakFeed[sad.channels()];

float speak[4][2];

for(int i; i < speak.size(); i++)
{
    90*i => speak[i][0];
}

sad.placement(speak);
enc.pos(90.0,0.0);

float place[][];
float encplace[];

sad.placement() @=> place;
enc.pos() @=> encplace;

fun void varImpulse(Impulse a, dur speed)
{
	while(true)
	{
		a.next(1.0);
        speed => now;
    }
}

for(int i; i < place.size(); i++)
{
    cherr <= "Speaker: " <= i+1 <= " angle: " <= 90*i <= IO.newline();
    for(int j; j < place[i].size(); j++)
    {
        cherr <= place[i][j] <= " ";
    }
    cherr <= IO.newline();
}

cherr <= "Virtual source @: ";
for(int i; i < encplace.size(); i++)
{
	cherr <= encplace[i] <= " ";
}
cherr <= IO.newline();

imp => enc => sad => blackhole;

for(int i; i < sad.channels(); i++)
{
    SpeakFeed[i].wavFilename("SAD_TEST_SPEAKER_"+(i+1));
    sad.chan(i) => SpeakFeed[i] => blackhole;
    SpeakFeed[i].record();
}

spork ~ varImpulse(imp, 34::ms);

while(true)
{
    float azi;
    for(int i; i < 360; i++)
    {
    	/*
        while(i >= azi)
        {
            azi+0.1 => azi;
            enc.pos(azi, 0);
        }
        */
        //enc.pos(90,0);
        10::ms => now;
    }
    for(int i; i < SpeakFeed.size(); i++)
    {
        SpeakFeed[i].closeFile();
    }
    me.exit();
}
