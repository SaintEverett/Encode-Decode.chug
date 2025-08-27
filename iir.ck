public class IIR extends Chugraph
{
    Delay z_[];
    Gain forward_mult[];
    Gain back_mult[];
    Gain sum[];
    int order;
    fun void IIR(int m_order)
    {
        m_order => order;
        (order-1) => z_.size;
        order => forward_mult.size;
        (order-1) => back_mult.size;
        order => sum.size;
        for(int i; i < z_.size(); i++)
        {
            z_[i].set((i+1)::samp, (i+2)::samp);
        }
        inlet => forward_mult[0] => sum[0] => outlet;
        for(1 => int i; i < order; i++)
        {
            inlet => forward_mult[i] => sum[i];
            sum[0] => back_mult[i] => sum[i];
            sum[i] => z_[i-1] => sum[i-1];
        }
    }
    fun void forward(float coeff[])
    {
        for(int i; i < coeff.size(); i++)
        {
            coeff[i] => forward_mult[i].gain;
        }
    }
    fun void back(float coeff[])
    {
        for(int i; i < coeff.size(); i++)
        {
            coeff[i] => back_mult[i].gain;
        }
    }
}
               