public class BFormatPlayer
{
    fun BFormatPlayer(string file)
    {
        SndBuf init(file); // we have to have some way of finding out how many channels there are
        if(!init.ready()) // can't open file
        {
            cherr <= IO.newline() <= "BFormatPlayer could not open file... exiting" <= IO.newline();
            me.exit();
        }
        BFormat.capacity(init.channels());
        for(int i; i < init.channels(); i++)
        {
            BFormat[i].read(file);
            BFormat[i].channel(i);
            BFormat[i].pos(0);
        }
    }
    fun void play()
    {
        for(int i; i < BFormat.size(); i++)
        {
            BFormat[i].rate(1.0);
        }
    }
    fun void play(float rate)
    {
        for(int i; i < BFormat.size(); i++)
        {
            BFormat[i].rate(rate);
        }
    }
    fun void play(float rate, int pos)
    {
        for(int i; i < BFormat.size(); i++)
        {
            BFormat[i].rate(rate);
            BFormat[i].pos(pos);
        }
    }
    fun UGen chan(int channel)
    {
        if(channel < BFormat.size()) return BFormat[channel];
        else { cherr <= IO.newline() <= "Index out of range" <= IO.newline(); me.exit(); return BFormat[0]; }
    }
    SndBuf BFormat[];
}