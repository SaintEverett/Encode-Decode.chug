/* ------------------------------------------------------------
author: "Everett M. Carpenter"
license: "MIT"
name: "untitled", "Crossover-Filter-Class"
Code generated with Faust 2.79.4 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif


class mydsp : public dsp {
	
 private:
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fRec3[2];
	float fConst3;
	float fRec4[2];
	float fConst4;
	float fRec0[2];
	float fRec1[2];
	float fRec7[2];
	float fRec8[2];
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("author", "Everett M. Carpenter");
		m->declare("compile_options", "-lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("filename", "untitled.dsp");
		m->declare("filters.lib/crossover2LR4:author", "Dario Sanfilippo");
		m->declare("filters.lib/crossover2LR4:copyright", "Copyright (C) 2022 Dario Sanfilippo <sanfilippo.dario@gmail.com>");
		m->declare("filters.lib/crossover2LR4:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpassLR4:author", "Dario Sanfilippo");
		m->declare("filters.lib/highpassLR4:copyright", "Copyright (C) 2022 Dario Sanfilippo <sanfilippo.dario@gmail.com>");
		m->declare("filters.lib/highpassLR4:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpassLR4:author", "Dario Sanfilippo");
		m->declare("filters.lib/lowpassLR4:copyright", "Copyright (C) 2022 Dario Sanfilippo <sanfilippo.dario@gmail.com>");
		m->declare("filters.lib/lowpassLR4:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/svf:author", "Oleg Nesterov");
		m->declare("filters.lib/svf:copyright", "Copyright (C) 2020 Oleg Nesterov <oleg@redhat.com>");
		m->declare("filters.lib/svf:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.1");
		m->declare("name", "untitled");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "1.2.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::tan(2356.1946f / std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate))));
		fConst1 = fConst0 * (fConst0 + 1.4142135f) + 1.0f;
		fConst2 = 2.0f / fConst1;
		fConst3 = fConst0 / fConst1;
		fConst4 = 1.0f / fConst1;
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec3[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec4[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec0[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec1[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec7[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec8[l5] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("untitled");
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = float(input0[i0]);
			float fTemp1 = fRec3[1] + fConst0 * (fTemp0 - fRec4[1]);
			fRec3[0] = fConst2 * fTemp1 - fRec3[1];
			float fTemp2 = fRec4[1] + fConst3 * fTemp1;
			fRec4[0] = 2.0f * fTemp2 - fRec4[1];
			float fRec5 = fConst4 * fTemp1;
			float fRec6 = fTemp2;
			float fTemp3 = fRec0[1] + fConst0 * (fRec6 - fRec1[1]);
			fRec0[0] = fConst2 * fTemp3 - fRec0[1];
			float fTemp4 = fRec1[1] + fConst3 * fTemp3;
			fRec1[0] = 2.0f * fTemp4 - fRec1[1];
			float fRec2 = fTemp4;
			output0[i0] = FAUSTFLOAT(fRec2);
			float fTemp5 = fRec6 + 1.4142135f * fRec5;
			float fTemp6 = fRec7[1] + fConst0 * (fTemp0 - (fTemp5 + fRec8[1]));
			fRec7[0] = fConst2 * fTemp6 - fRec7[1];
			float fTemp7 = fRec8[1] + fConst3 * fTemp6;
			fRec8[0] = 2.0f * fTemp7 - fRec8[1];
			float fRec9 = fConst4 * fTemp6;
			float fRec10 = fTemp7;
			output1[i0] = FAUSTFLOAT(fTemp0 - (1.4142135f * (fRec5 + fRec9) + fRec6 + fRec10));
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
		}
	}

};

#endif
