Encode3 encode;
Gain sum(1/encode.chans())[encode.chans()];
SinOsc osc(356);
float array[16];
for(int i; i < array.size(); i++) {
    Math.random2f(-1.0,1.0) => array[i];
}

encode.coeff(array);

for(int i; i < array.size(); i++) {
    cherr <= "Real: " <= array[i] <= " | Chugin: " <= encode.geti(i) <= IO.newline();
}
for(int i; i < encode.chans(); i++) {
   
    osc => encode.chan(i) => sum[i] => dac.chan(i%1);
}
