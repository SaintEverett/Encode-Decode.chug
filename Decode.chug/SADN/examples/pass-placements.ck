Encode1 enc;
SAD1 sad;

SinOsc sin(452.0);

float speak[4][2];

for(int i; i < speak.size(); i++)
{
    90*i => speak[i][0];
    15.0 => speak[i][1]; 
}

sad.placement(speak);

float place[][];

sad.placement() @=> place;

for(int i; i < place.size(); i++)
{
    cherr <= "Speaker: " <= i+1 <= IO.newline();
    for(int j; j < place[i].size(); j++)
    {
        cherr <= place[i][j] <= " ";
    }
    cherr <= IO.newline();
}

sin => 