// Calculation of re and rv in first order models as defined by Gerzon

// "Here we list some basic "primitive" models, describing them in terms of the information received by the ear/brain system when responding to a number of n equally distant sound signals P placed in direction with direction cosines (x,y,z).
@import "../classes/Speaker.ck"
@import "../classes/Source.ck"

Speaker speak[4]; // first order, 4 speakers
Source sound(45.0,15.0); // one sound source with azimuth 45 degrees and zenith 15 degrees
AmbiMath calc;
float source_spherical[2][4];
float speak_spherical[4][4];
vec3 energy;
[45.0, 135.0, 225.0, 315.0] @=> float direction[]; // azimuths of speakers
[0.0, 0.0, 0.0, 0.0] @=> float elevation[]; // zeniths of speakers

calc.all(15.0,5.0,source_spherical[0],1);
calc.all(160.0,-15.0,source_spherical[1],1);

fun vec3 velocity(float sh[][], vec3 u[])
{
    float gain[sh.size()];
    if(sh.size() == sh[0].size())
    {    
        for(int i; i < sh.size(); i++)
        {
            1.0 => gain[i];
            for(int j; j < sh[i].size(); j++)
            {
                if(Math.fabs(sh[j][i]) > 0) sh[j][i] *=> gain[i];
            }
        }
    }
    vec3 top;
    float bottom;
    for(int i; i < u.size(); i++)
    {
        gain[i]*u[i] +=> top;
        gain[i] +=> bottom;
    }

    return (top * 1.0/bottom);
}

fun vec3 velocity(float sh[][], vec3 u[], float source[][]) // with source input
{
    float gain[sh.size()];
    float total;
    for(int i; i < source.size(); i++)
    {  
        1.0 => total;
        for(int j; j < source[i].size(); j++)
        {
            if(Math.fabs(source[i][j]) > 0) source[i][j] *=> total;
        }
    }
    if(sh.size() == sh[0].size())
    {    
        for(int i; i < sh.size(); i++)
        {
            (total*1.0) => gain[i];
            for(int j; j < sh[i].size(); j++)
            {
                if(Math.fabs(sh[j][i]) > 0) sh[j][i] *=> gain[i];
            }
        }
    }
    vec3 top;
    float bottom;
    for(int i; i < u.size(); i++)
    {
        gain[i]*u[i] +=> top;
        gain[i] +=> bottom;
    }

    return (top * 1.0/bottom);
}


for(int i; i < speak.size(); i++)
{
    float temp[4];
    speak[i].update(direction[i], elevation[i]);   
    calc.all(direction[i],elevation[i],temp,1);
    for(int j; j < speak_spherical[i].size(); j++)
    {
        temp[j] => speak_spherical[j][i];
    }
    /*
    cherr <= "Speaker: " <= i <= IO.newline();
    cherr <= "Length: " <= speak[i].placement.magnitude() <= IO.newline();
    cherr <= "x: " <= speak[i].placement.x <= IO.newline();
    cherr <= "y: " <= speak[i].placement.y <= IO.newline();
    cherr <= "z: " <= speak[i].placement.z <= IO.newline();
    cherr <= IO.newline();
    */
}
/*
cherr <= "Source: " <= 1 <= IO.newline();
cherr <= "Length: " <= sound.placement.magnitude() <= IO.newline();
cherr <= "x: " <= sound.placement.x <= IO.newline();
cherr <= "y: " <= sound.placement.y <= IO.newline();
cherr <= "z: " <= sound.placement.z <= IO.newline();
*/
vec3 units[4];
for(int i; i < speak_spherical.size(); i++)
{
    speak[i].placement => units[i];
    for(int j; j < speak_spherical[i].size(); j++)
    {
        cherr <= speak_spherical[i][j] <= " ";
    }
    cherr <= IO.newline();
}
cherr <= IO.newline();

velocity(speak_spherical, units, source_spherical) => vec3 r_v;

cherr <= "Rv Velocity: " <= 1 <= IO.newline();
cherr <= "Length: " <= r_v.magnitude() <= IO.newline();
cherr <= "x: " <= r_v.x <= IO.newline();
cherr <= "y: " <= r_v.y <= IO.newline();
cherr <= "z: " <= r_v.z <= IO.newline();