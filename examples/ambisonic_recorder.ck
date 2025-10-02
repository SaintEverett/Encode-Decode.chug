//--------------------------SETUP-------------------------------
string name;
if(me.args()) me.arg(0) => name;
else me.exit();
1 => int N_OBJECTS; // how many sound sources
["W","Y","Z","X","V","T","R","S","U","Q","O","M","K","L","N","P"] @=> string letters[]; // symbols

Encode2 enc; // ENCODE
WvOut record[enc.channels()]; // record
Gain input; // input "fader"
input.gain(0.5);
for(int i; i < enc.channels(); i++)
{
    enc.chan(i) => record[i] => blackhole;
    record[i].wavFilename(name+"_"+i);
}
//--------------------------------------------------------------

Impulse imp;
NRev rev;
rev.mix(0.25);
imp => rev => input => dac;
input => enc;
float direction;
15.0 => float elevation;
  
for(int tick; tick < 60; tick++)
{
    imp.next(1.0);
    (tick/60) * 2 * pi => direction;
    enc.pos(direction,elevation);
    500::ms => now;
}

for(int i; i < record.size(); i++)
{
    record[i].closeFile();
}

