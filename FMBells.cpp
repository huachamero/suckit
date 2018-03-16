#include "FMBells.h"

namespace FMBells {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Delta __m_delta_8;
	PlusEquals __m_pluseq_21;
	PlusEquals __m_pluseq_12;
	PlusEquals __m_pluseq_16;
	PlusEquals __m_pluseq_20;
	int __exception;
	int vectorsize;
	t_sample __m_slide_13;
	t_sample samplerate;
	t_sample m_C_4;
	t_sample __m_slide_17;
	t_sample m_D_3;
	t_sample __m_slide_9;
	t_sample m_history_7;
	t_sample m_B_1;
	t_sample m_Push_5;
	t_sample m_A_2;
	t_sample m_l_6;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_B_1 = 0;
		m_A_2 = 0;
		m_D_3 = 0;
		m_C_4 = 0;
		m_Push_5 = 0;
		m_l_6 = 0;
		m_history_7 = 0;
		__m_delta_8.reset(0);
		__m_slide_9 = 0;
		__m_pluseq_12.reset(0);
		__m_slide_13 = 0;
		__m_pluseq_16.reset(0);
		__m_slide_17 = 0;
		__m_pluseq_20.reset(0);
		__m_pluseq_21.reset(0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample expr_104 = ((m_A_2 * 60) + 20);
		t_sample mul_68 = (m_D_3 * 4);
		int int_67 = int(mul_68);
		t_sample div_66 = (int_67 * 0.25);
		t_sample mul_69 = (div_66 * 0.000216);
		t_sample add_70 = (mul_69 + 0.999712);
		t_sample iup_10 = (1 / maximum(1, abs(300)));
		t_sample idown_11 = (1 / maximum(1, abs(300)));
		t_sample iup_14 = (1 / maximum(1, abs(300)));
		t_sample idown_15 = (1 / maximum(1, abs(300)));
		t_sample iup_18 = (1 / maximum(1, abs(300)));
		t_sample idown_19 = (1 / maximum(1, abs(300)));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample delta_81 = __m_delta_8(m_Push_5);
			t_sample gtep_80 = ((delta_81 >= 1) ? delta_81 : 0);
			t_sample gen_82 = gtep_80;
			t_sample sub_92 = (m_l_6 - m_history_7);
			t_sample mul_93 = (sub_92 * 0.98);
			t_sample mul_71 = (m_history_7 * add_70);
			__m_slide_9 = fixdenorm((__m_slide_9 + (((expr_104 > __m_slide_9) ? iup_10 : idown_11) * (expr_104 - __m_slide_9))));
			t_sample slide_74 = __m_slide_9;
			int int_75 = int(slide_74);
			t_sample mtof_78 = mtof(int_75, 440);
			t_sample mul_77 = (mtof_78 * 2);
			t_sample mul_76 = (mul_77 * 3.1415926535898);
			t_sample div_84 = safediv(mul_76, samplerate);
			t_sample plusequals_89 = __m_pluseq_12.post(div_84, 0, 0);
			t_sample cos_88 = cos(plusequals_89);
			__m_slide_13 = fixdenorm((__m_slide_13 + (((m_B_1 > __m_slide_13) ? iup_14 : idown_15) * (m_B_1 - __m_slide_13))));
			t_sample slide_73 = __m_slide_13;
			t_sample mul_61 = (slide_73 * 12);
			int int_60 = int(mul_61);
			t_sample div_59 = (int_60 * 0.083333333333333);
			t_sample clamp_65 = ((div_59 <= 0.1) ? 0.1 : ((div_59 >= 0.9) ? 0.9 : div_59));
			t_sample mul_83 = (clamp_65 * 5);
			t_sample mul_100 = (div_84 * mul_83);
			t_sample plusequals_99 = __m_pluseq_16.post(mul_100, 0, 0);
			t_sample sin_98 = sin(plusequals_99);
			__m_slide_17 = fixdenorm((__m_slide_17 + (((m_C_4 > __m_slide_17) ? iup_18 : idown_19) * (m_C_4 - __m_slide_17))));
			t_sample slide_72 = __m_slide_17;
			t_sample mul_64 = (slide_72 * 12);
			int int_63 = int(mul_64);
			t_sample div_62 = (int_63 * 0.083333333333333);
			t_sample mul_97 = (div_62 * 5);
			t_sample mul_85 = (mul_100 * mul_97);
			t_sample mul_87 = (mul_85 * cos_88);
			t_sample plusequals_91 = __m_pluseq_20.post((mul_87 + mul_100), 0, 0);
			t_sample sin_90 = sin(plusequals_91);
			t_sample mul_86 = (sin_90 * m_l_6);
			t_sample out2 = mul_86;
			t_sample mul_101 = (div_84 * mul_97);
			t_sample mul_96 = (mul_101 * sin_98);
			t_sample plusequals_103 = __m_pluseq_21.post((div_84 + mul_96), 0, 0);
			t_sample sin_102 = sin(plusequals_103);
			t_sample mul_94 = (sin_102 * m_l_6);
			t_sample out1 = mul_94;
			t_sample l_next_105 = fixdenorm((m_history_7 + mul_93));
			t_sample history_95_next_106 = fixdenorm((gen_82 + mul_71));
			m_l_6 = l_next_105;
			m_history_7 = history_95_next_106;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_B(t_param _value) {
		m_B_1 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_A(t_param _value) {
		m_A_2 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_D(t_param _value) {
		m_D_3 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_C(t_param _value) {
		m_C_4 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_Push(t_param _value) {
		m_Push_5 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 5; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_A(value); break;
		case 1: self->set_B(value); break;
		case 2: self->set_C(value); break;
		case 3: self->set_D(value); break;
		case 4: self->set_Push(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_A_2; break;
		case 1: *value = self->m_B_1; break;
		case 2: *value = self->m_C_4; break;
		case 3: *value = self->m_D_3; break;
		case 4: *value = self->m_Push_5; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(5 * sizeof(ParamInfo));
	self->__commonstate.numparams = 5;
	// initialize parameter 0 ("m_A_2")
	pi = self->__commonstate.params + 0;
	pi->name = "A";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_A_2;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_B_1")
	pi = self->__commonstate.params + 1;
	pi->name = "B";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_B_1;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_C_4")
	pi = self->__commonstate.params + 2;
	pi->name = "C";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_C_4;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_D_3")
	pi = self->__commonstate.params + 3;
	pi->name = "D";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_D_3;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_Push_5")
	pi = self->__commonstate.params + 4;
	pi->name = "Push";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_Push_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // FMBells::
