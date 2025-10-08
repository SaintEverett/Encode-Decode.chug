public class Speaker
{
    fun float degreeRad(float degree)
    {
        return (degree * (pi/180)); 
    }

    fun void Speaker(float direction, float elevation)
    {
        (Math.sin(degreeRad(direction))*Math.cos(degreeRad(elevation))) => x;
        (Math.cos(degreeRad(direction))*Math.cos(degreeRad(elevation))) => y;
        (Math.sin(degreeRad(elevation))) => z;
        x => placement.x;
        y => placement.y;
        z => placement.z;
    }

    fun void update(float direction, float elevation)
    {
        (Math.sin(degreeRad(direction))*Math.cos(degreeRad(elevation))) => x;
        (Math.cos(degreeRad(direction))*Math.cos(degreeRad(elevation))) => y;
        (Math.sin(degreeRad(elevation))) => z;
        x => placement.x;
        y => placement.y;
        z => placement.z;
    }

    float x;
    float y;
    float z;
    vec3 placement;
}