Encode3 encode;
Gain sum(0.225)[16];
SinOsc osc(356);
float array[16];
for(int i; i < array.size(); i++) {
    Math.random2f(-1.0,1.0) => array[i];
}

fun void shuffle(float storage[]) {
    for(int i; i < storage.size(); i++) {
    Math.random2f(-1.0,1.0) => storage[i];
    }
    for(int i; i < storage.size(); i++) {
    cherr <= "Real: " <= storage[i] <= " | Chugin: " <= encode.geti(i) <= IO.newline();
    }
}

shuffle(array);
encode.coeff(array);

for(int i; i < 16; i++) {
   
    osc => encode.chan(i) => sum[i] => dac.chan(i%1);
}

while(true){
    shuffle(array);
    encode.coeff(array);
    800::ms => now; 
}
