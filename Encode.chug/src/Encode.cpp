//-----------------------------------------------------------------------------
// Author: Everett M. Carpenter
// Date: Summer 2025
//-----------------------------------------------------------------------------
// happy chucking & chugging!
//-----------------------------------------------------------------------------

// include chugin header
#include "chugin.h"

// general includes
#include <stdio.h>
#include <limits.h>
#include <math.h>

const t_CKFLOAT ZERO_THRESHOLD = 1e-3; // this is the threshold to swap coordinates, if the input sample is less than this, change coefficients

//-----------------------------------------------------------------------------
// class definition for internal chugin data
// (NOTE this isn't strictly necessary, but is one example of a recommended approach)
//-----------------------------------------------------------------------------
class EncodeN
{
public:
    EncodeN(t_CKFLOAT fs, t_CKUINT chan) :
        channel_count(chan)
    {
        channel_matrix = new t_CKFLOAT[channel_count]; // create arrays for these guys
        temp_matrix = new t_CKFLOAT[channel_count];
    }
    ~EncodeN() 
    {
        delete[] channel_matrix;
        delete[] temp_matrix;
    }
    // for chugins extending UGen
    void tick( SAMPLE* in, SAMPLE* out, int nframes)
    {
        for (int f = 0; f < nframes; f++) 
        {
            zeroCrossing = abs(in[f]) < ZERO_THRESHOLD ? TRUE : FALSE; //  less that threshold? zeroCrossing TRUE else FALSE
        }
        
        if (zeroCrossing && !arrayEqual) // zero crossing and matrices aren't the same?
        {
            for (int i = 0; i < channel_count; i++) 
            {
                channel_matrix[i] = temp_matrix[i]; // swap it out
            }
            arrayEqual = TRUE;  // they are the same
        }

        memset(out, 0, sizeof(SAMPLE) * channel_count * nframes); // clear

        for (int f = 0; f < nframes; f++)
        {
            for (int i = 0; i < channel_count; i++)
            {   
                out[f * channel_count + i] = (in[f*channel_count] * channel_matrix[i]); //
            }
        }

    }
    void set_coefficients(Chuck_ArrayFloat* coord, CK_DL_API API)
    {
        int size = (API->object->array_float_size(coord));
        if (size >= channel_count)
        {
            for (int i = 0; i < size;i++)
            {
                temp_matrix[i] = (API->object->array_float_get_idx(coord, i));
            }
            arrayEqual = FALSE; // new matrix automatically means it is not equal to the current
        }
    }
    t_CKFLOAT get_i(int index)
    {
        if (index < channel_count) { return channel_matrix[index]; }
        else return NULL;
    }
    void set_i(t_CKFLOAT value, t_CKUINT index)
    {
        if (index < channel_count) 
        { 
            temp_matrix[index] = value; 
            arrayEqual = FALSE;
        }
        else NULL;
    }
    t_CKUINT get_chans() { return channel_count; }
protected:
    // instance data
    t_CKUINT order = 0;
    t_CKUINT channel_count = 0;
    t_CKFLOAT *channel_matrix;
    t_CKFLOAT *temp_matrix;
    bool zeroCrossing = FALSE;
    bool arrayEqual = TRUE; // if 1, temp matrix and current matrix are equal. if 0, temp needs to be copied to current
};

class Encode1 : public EncodeN
{
public:
    Encode1(t_CKFLOAT fs) : EncodeN(fs, 4)
    {
        order = 1;
        channel_count = 4;
    }   
};

class Encode2 : public EncodeN
{
public:
    Encode2(t_CKFLOAT fs) : EncodeN(fs, 9)
    {
        order = 2;
        channel_count = 9;
    }
};

class Encode3 : public EncodeN
{
public:
    Encode3(t_CKFLOAT fs) : EncodeN(fs, 16)
    {
        order = 3;
        channel_count = 16;
    }
};

class Encode4 : public EncodeN
{
public:
    Encode4(t_CKFLOAT fs) : EncodeN(fs, 25)
    {
        order = 4;
        channel_count = 25;
    }
};

class Encode5 : public EncodeN
{
public:
    Encode5(t_CKFLOAT fs) : EncodeN(fs, 36)
    {
        order = 5;
        channel_count = 36;
    }
};

// declaration of chugin constructor
// Encode1
CK_DLL_CTOR(encode1_ctor);
CK_DLL_DTOR(encode1_dtor);
CK_DLL_TICKF(encode1_tickf);
CK_DLL_MFUN(encode1_geti);
CK_DLL_MFUN(encode1_seti);
CK_DLL_MFUN(encode1_coefficients);
CK_DLL_MFUN(encode1_get_chans);
t_CKINT encode1_data_offset = 0;
// Encode2
CK_DLL_CTOR(encode2_ctor);
CK_DLL_DTOR(encode2_dtor);
CK_DLL_TICKF(encode2_tickf);
CK_DLL_MFUN(encode2_geti);
CK_DLL_MFUN(encode2_seti);
CK_DLL_MFUN(encode2_coefficients);
CK_DLL_MFUN(encode2_get_chans);
t_CKINT encode2_data_offset = 0;
// Encode3
CK_DLL_CTOR(encode3_ctor);
CK_DLL_DTOR(encode3_dtor);
CK_DLL_TICKF(encode3_tickf);
CK_DLL_MFUN(encode3_geti);
CK_DLL_MFUN(encode3_seti);
CK_DLL_MFUN(encode3_coefficients);
CK_DLL_MFUN(encode3_get_chans);
t_CKINT encode3_data_offset = 0;
// Encode4
CK_DLL_CTOR(encode4_ctor);
CK_DLL_DTOR(encode4_dtor);
CK_DLL_TICKF(encode4_tickf);
CK_DLL_MFUN(encode4_geti);
CK_DLL_MFUN(encode4_seti);
CK_DLL_MFUN(encode4_coefficients);
CK_DLL_MFUN(encode4_get_chans);
t_CKINT encode4_data_offset = 0;
// Encode5
CK_DLL_CTOR(encode5_ctor);
CK_DLL_DTOR(encode5_dtor);
CK_DLL_TICKF(encode5_tickf);
CK_DLL_MFUN(encode5_geti);
CK_DLL_MFUN(encode5_seti);
CK_DLL_MFUN(encode5_coefficients);
CK_DLL_MFUN(encode5_get_chans);
t_CKINT encode5_data_offset = 0;

//-----------------------------------------------------------------------------
// info function: ChucK calls this when loading/probing the chugin
// NOTE: please customize these info fields below; they will be used for
// chugins loading, probing, and package management and documentation
//-----------------------------------------------------------------------------
CK_DLL_INFO( Encode )
{
    // the version string of this chugin, e.g., "v1.2.1"
    QUERY->setinfo( QUERY, CHUGIN_INFO_CHUGIN_VERSION, "" );
    // the author(s) of this chugin, e.g., "Alice Baker & Carl Donut"
    QUERY->setinfo( QUERY, CHUGIN_INFO_AUTHORS, "Everett M. Carpenter" );
    // text description of this chugin; what is it? what does it do? who is it for?
    QUERY->setinfo( QUERY, CHUGIN_INFO_DESCRIPTION, "Ambisonic encoding within ChucK" );
    // (optional) URL of the homepage for this chugin
    QUERY->setinfo( QUERY, CHUGIN_INFO_URL, "" );
    // (optional) contact email
    QUERY->setinfo( QUERY, CHUGIN_INFO_EMAIL, "" );
}


//-----------------------------------------------------------------------------
// query function: ChucK calls this when loading the chugin
// modify this function to define this chugin's API and language extensions
//-----------------------------------------------------------------------------
CK_DLL_QUERY( Encode )
{
    // generally, don't change this...
    QUERY->setname( QUERY, "Encode" );

    // ------------------------------------------------------------------------
    // begin class definition(s) Encode1; will be compiled, verified,
    // and added to the chuck host type system for use
    // ------------------------------------------------------------------------
    // NOTE to create a non-UGen class, change the second argument
    // to extend a different ChucK class (e.g., "Object")
    QUERY->begin_class( QUERY, "Encode1", "UGen" );
    // register the destructor (probably no need to change)
    QUERY->add_ctor(QUERY, encode1_ctor);
    QUERY->add_dtor( QUERY, encode1_dtor );
    QUERY->add_ugen_funcf( QUERY, encode1_tickf, NULL, 1, 4 );  
    QUERY->add_mfun(QUERY, encode1_geti, "float", "geti");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_mfun(QUERY, encode1_coefficients, "void", "coeff");
    QUERY->add_arg(QUERY, "float[]", "coordinates");
    QUERY->add_mfun(QUERY, encode1_get_chans, "int", "chans");
    QUERY->add_mfun(QUERY, encode1_seti, "void", "seti");
    QUERY->add_arg(QUERY, "float", "value");
    QUERY->add_arg(QUERY, "int", "channel_index");
    // this reserves a variable in the ChucK internal class to store 
    // referene to the c++ class we defined above
    encode1_data_offset = QUERY->add_mvar( QUERY, "int", "@e_data", false );
    QUERY->end_class(QUERY);

    // ------------------------------------------------------------------------
    // begin class definition(s) Encode2; will be compiled, verified,
    // and added to the chuck host type system for use
    // ------------------------------------------------------------------------
    // NOTE to create a non-UGen class, change the second argument
    // to extend a different ChucK class (e.g., "Object")
    QUERY->begin_class(QUERY, "Encode2", "UGen");
    // register the destructor (probably no need to change)
    QUERY->add_ctor(QUERY, encode2_ctor);
    QUERY->add_dtor(QUERY, encode2_dtor);
    QUERY->add_ugen_funcf(QUERY, encode2_tickf, NULL, 1, 9);
    QUERY->add_mfun(QUERY, encode2_geti, "float", "geti");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_mfun(QUERY, encode2_coefficients, "void", "coeff");
    QUERY->add_arg(QUERY, "float[]", "coordinates");
    QUERY->add_mfun(QUERY, encode2_get_chans, "int", "chans");
    QUERY->add_mfun(QUERY, encode2_seti, "void", "seti");
    QUERY->add_arg(QUERY, "float", "value");
    QUERY->add_arg(QUERY, "int", "channel_index");
    // this reserves a variable in the ChucK internal class to store 
    // referene to the c++ class we defined above
    encode2_data_offset = QUERY->add_mvar(QUERY, "int", "@e_data", false);
    QUERY->end_class(QUERY);

    // ------------------------------------------------------------------------
    // begin class definition(s) Encode3; will be compiled, verified,
    // and added to the chuck host type system for use
    // ------------------------------------------------------------------------
    // NOTE to create a non-UGen class, change the second argument
    // to extend a different ChucK class (e.g., "Object")
    QUERY->begin_class(QUERY, "Encode3", "UGen");
    // register the destructor (probably no need to change)
    QUERY->add_ctor(QUERY, encode3_ctor);
    QUERY->add_dtor(QUERY, encode3_dtor);
    QUERY->add_ugen_funcf(QUERY, encode3_tickf, NULL, 1, 16);
    QUERY->add_mfun(QUERY, encode3_geti, "float", "geti");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_mfun(QUERY, encode3_coefficients, "void", "coeff");
    QUERY->add_arg(QUERY, "float[]", "coordinates");
    QUERY->add_mfun(QUERY, encode3_get_chans, "int", "chans");
    QUERY->add_mfun(QUERY, encode3_seti, "void", "seti");
    QUERY->add_arg(QUERY, "float", "value");
    QUERY->add_arg(QUERY, "int", "channel_index");
    // this reserves a variable in the ChucK internal class to store 
    // referene to the c++ class we defined above
    encode3_data_offset = QUERY->add_mvar(QUERY, "int", "@e_data", false);
    QUERY->end_class(QUERY);

    // ------------------------------------------------------------------------
    // begin class definition(s) Encode4; will be compiled, verified,
    // and added to the chuck host type system for use
    // ------------------------------------------------------------------------
    // NOTE to create a non-UGen class, change the second argument
    // to extend a different ChucK class (e.g., "Object")
    QUERY->begin_class(QUERY, "Encode4", "UGen");
    // register the destructor (probably no need to change)
    QUERY->add_ctor(QUERY, encode4_ctor);
    QUERY->add_dtor(QUERY, encode4_dtor);
    QUERY->add_ugen_funcf(QUERY, encode4_tickf, NULL, 1, 25);
    QUERY->add_mfun(QUERY, encode4_geti, "float", "geti");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_mfun(QUERY, encode4_coefficients, "void", "coeff");
    QUERY->add_arg(QUERY, "float[]", "coordinates");
    QUERY->add_mfun(QUERY, encode4_get_chans, "int", "chans");
    QUERY->add_mfun(QUERY, encode4_seti, "void", "seti");
    QUERY->add_arg(QUERY, "float", "value");
    QUERY->add_arg(QUERY, "int", "channel_index");
    // this reserves a variable in the ChucK internal class to store 
    // referene to the c++ class we defined above
    encode4_data_offset = QUERY->add_mvar(QUERY, "int", "@e_data", false);
    QUERY->end_class(QUERY);

    // ------------------------------------------------------------------------
    // begin class definition(s) Encode5; will be compiled, verified,
    // and added to the chuck host type system for use
    // ------------------------------------------------------------------------
    // NOTE to create a non-UGen class, change the second argument
    // to extend a different ChucK class (e.g., "Object")
    QUERY->begin_class(QUERY, "Encode5", "UGen");
    // register the destructor (probably no need to change)
    QUERY->add_ctor(QUERY, encode5_ctor);
    QUERY->add_dtor(QUERY, encode5_dtor);
    QUERY->add_ugen_funcf(QUERY, encode5_tickf, NULL, 1, 36);
    QUERY->add_mfun(QUERY, encode5_geti, "float", "geti");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_mfun(QUERY, encode5_coefficients, "void", "coeff");
    QUERY->add_arg(QUERY, "float[]", "coordinates");
    QUERY->add_mfun(QUERY, encode5_get_chans, "int", "chans");
    QUERY->add_mfun(QUERY, encode5_seti, "void", "seti");
    QUERY->add_arg(QUERY, "float", "value");
    QUERY->add_arg(QUERY, "int", "channel_index");
    // this reserves a variable in the ChucK internal class to store 
    // referene to the c++ class we defined above
    encode5_data_offset = QUERY->add_mvar(QUERY, "int", "@e_data", false);
    QUERY->end_class(QUERY);

    // ------------------------------------------------------------------------
    // end the class(es) definition
    // IMPORTANT: this MUST be called to each class definition!
    // ------------------------------------------------------------------------

    // wasn't that a breeze?
    return TRUE;
}

//=================================================//
// ************************************************//
//                                                 //   
// Encode1 DLL definitions ; Everett M. Carpenter  //
//                                                 //
// ************************************************//
//=================================================//
// implementation for the default constructor
CK_DLL_CTOR( encode1_ctor )
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT( SELF, encode1_data_offset ) = 0;
    
    // instantiate our internal c++ class representation
    Encode1 * encodencode_obj = new Encode1( API->vm->srate(VM) );
    
    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT( SELF, encode1_data_offset ) = (t_CKINT)encodencode_obj;
}

// implementation for the destructor
CK_DLL_DTOR( encode1_dtor )
{
    // get our c++ class pointer
    Encode1 * encode_obj = (Encode1*)OBJ_MEMBER_INT( SELF, encode1_data_offset );
    // clean up (this macro tests for NULL, deletes, and zeros out the variable)
    CK_SAFE_DELETE( encode_obj );
    // set the data field to 0
    OBJ_MEMBER_INT( SELF, encode1_data_offset ) = 0;
}

CK_DLL_MFUN( encode1_geti )
{
    int index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode1* encode_obj = (Encode1*)OBJ_MEMBER_INT(SELF, encode1_data_offset);
    if (encode_obj) { RETURN->v_float = encode_obj->get_i(index); }
}

// implementation for tick function (relevant only for UGens)
CK_DLL_TICKF( encode1_tickf )
{
    // get our c++ class pointer
    Encode1 * encode_obj = (Encode1*)OBJ_MEMBER_INT(SELF, encode1_data_offset);
 
    // invoke our tick function; store in the magical out variable
    if (encode_obj)
    {
        encode_obj->tick(in, out, nframes);
    }
    // yes
    return TRUE;
}

CK_DLL_MFUN(encode1_coefficients)
{
    // get our c++ class pointer
    Encode1* encode_obj = (Encode1*)OBJ_MEMBER_INT(SELF, encode1_data_offset);
    Chuck_ArrayFloat* coefficients = (Chuck_ArrayFloat*)GET_NEXT_OBJECT(ARGS);
    encode_obj->set_coefficients(coefficients, API);
}

CK_DLL_MFUN(encode1_get_chans)
{
    // get our c++ class pointer
    Encode1* encode_obj = (Encode1*)OBJ_MEMBER_INT(SELF, encode1_data_offset);
    RETURN->v_int = encode_obj->get_chans();
}

CK_DLL_MFUN(encode1_seti)
{
    float input_value = GET_NEXT_FLOAT(ARGS);
    int input_index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode1* encode_obj = (Encode1*)OBJ_MEMBER_INT(SELF, encode1_data_offset);
    if (encode_obj) { encode_obj->set_i(input_value, input_index); }
}

//=================================================//
// ************************************************//
//                                                 //   
// Encode2 DLL definitions ; Everett M. Carpenter  //
//                                                 //
// ************************************************//
//=================================================//
// implementation for the default constructor
CK_DLL_CTOR(encode2_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, encode2_data_offset) = 0;

    // instantiate our internal c++ class representation
    Encode2* encode_obj = new Encode2(API->vm->srate(VM));

    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, encode2_data_offset) = (t_CKINT)encode_obj;
}

// implementation for the destructor
CK_DLL_DTOR(encode2_dtor)
{
    // get our c++ class pointer
    Encode2* encode_obj = (Encode2*)OBJ_MEMBER_INT(SELF, encode2_data_offset);
    // clean up (this macro tests for NULL, deletes, and zeros out the variable)
    CK_SAFE_DELETE(encode_obj);
    // set the data field to 0
    OBJ_MEMBER_INT(SELF, encode2_data_offset) = 0;
}

// implementation for tick function (relevant only for UGens)
CK_DLL_TICKF(encode2_tickf)
{
    // get our c++ class pointer
    Encode2* encode_obj = (Encode2*)OBJ_MEMBER_INT(SELF, encode2_data_offset);

    // invoke our tick function; store in the magical out variable
    if (encode_obj)
    {
        encode_obj->tick(in, out, nframes);
    }
    // yes
    return TRUE;
}

CK_DLL_MFUN(encode2_geti)
{
    int index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode2* encode_obj = (Encode2*)OBJ_MEMBER_INT(SELF, encode2_data_offset);
    if (encode_obj) { RETURN->v_float = encode_obj->get_i(index); }
}

CK_DLL_MFUN(encode2_coefficients)
{
    // get our c++ class pointer
    Encode2* encode_obj = (Encode2*)OBJ_MEMBER_INT(SELF, encode2_data_offset);
    Chuck_ArrayFloat* coefficients = (Chuck_ArrayFloat*)GET_NEXT_OBJECT(ARGS);
    encode_obj->set_coefficients(coefficients, API);
}

CK_DLL_MFUN(encode2_get_chans)
{
    // get our c++ class pointer
    Encode2* encode_obj = (Encode2*)OBJ_MEMBER_INT(SELF, encode2_data_offset);
    RETURN->v_int = encode_obj->get_chans();
}

CK_DLL_MFUN(encode2_seti)
{
    float input_value = GET_NEXT_FLOAT(ARGS);
    int input_index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode2* encode_obj = (Encode2*)OBJ_MEMBER_INT(SELF, encode2_data_offset);
    if (encode_obj) { encode_obj->set_i(input_value, input_index); }
}

//=================================================//
// ************************************************//
//                                                 //   
// Encode3 DLL definitions ; Everett M. Carpenter  //
//                                                 //
// ************************************************//
//=================================================//
// implementation for the default constructor
CK_DLL_CTOR(encode3_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, encode3_data_offset) = 0;

    // instantiate our internal c++ class representation
    Encode3* encode_obj = new Encode3(API->vm->srate(VM));

    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, encode3_data_offset) = (t_CKINT)encode_obj;
}

// implementation for the destructor
CK_DLL_DTOR(encode3_dtor)
{
    // get our c++ class pointer
    Encode3* encode_obj = (Encode3*)OBJ_MEMBER_INT(SELF, encode3_data_offset);
    // clean up (this macro tests for NULL, deletes, and zeros out the variable)
    CK_SAFE_DELETE(encode_obj);
    // set the data field to 0
    OBJ_MEMBER_INT(SELF, encode3_data_offset) = 0;
}

// implementation for tick function (relevant only for UGens)
CK_DLL_TICKF(encode3_tickf)
{
    // get our c++ class pointer
    Encode3* encode_obj = (Encode3*)OBJ_MEMBER_INT(SELF, encode3_data_offset);

    // invoke our tick function; store in the magical out variable
    if (encode_obj)
    {
        encode_obj->tick(in, out, nframes);
    }
    // yes
    return TRUE;
}

CK_DLL_MFUN(encode3_geti)
{
    int index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode3* encode_obj = (Encode3*)OBJ_MEMBER_INT(SELF, encode3_data_offset);
    if (encode_obj) { RETURN->v_float = encode_obj->get_i(index); }
}

CK_DLL_MFUN(encode3_coefficients)
{
    // get our c++ class pointer
    Encode3* encode_obj = (Encode3*)OBJ_MEMBER_INT(SELF, encode3_data_offset);
    Chuck_ArrayFloat* coefficients = (Chuck_ArrayFloat*)GET_NEXT_OBJECT(ARGS);
    encode_obj->set_coefficients(coefficients, API);
}

CK_DLL_MFUN(encode3_get_chans)
{
    // get our c++ class pointer
    Encode3* encode_obj = (Encode3*)OBJ_MEMBER_INT(SELF, encode3_data_offset);
    RETURN->v_int = encode_obj->get_chans();
}

CK_DLL_MFUN(encode3_seti)
{
    float input_value = GET_NEXT_FLOAT(ARGS);
    int input_index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode3* encode_obj = (Encode3*)OBJ_MEMBER_INT(SELF, encode3_data_offset);
    if (encode_obj) { encode_obj->set_i(input_value, input_index); }
}

//=================================================//
// ************************************************//
//                                                 //   
// Encode4 DLL definitions ; Everett M. Carpenter  //
//                                                 //
// ************************************************//
//=================================================//
// implementation for the default constructor
CK_DLL_CTOR(encode4_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, encode4_data_offset) = 0;

    // instantiate our internal c++ class representation
    Encode4* encode_obj = new Encode4(API->vm->srate(VM));

    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, encode4_data_offset) = (t_CKINT)encode_obj;
}

// implementation for the destructor
CK_DLL_DTOR(encode4_dtor)
{
    // get our c++ class pointer
    Encode4* encode_obj = (Encode4*)OBJ_MEMBER_INT(SELF, encode4_data_offset);
    // clean up (this macro tests for NULL, deletes, and zeros out the variable)
    CK_SAFE_DELETE(encode_obj);
    // set the data field to 0
    OBJ_MEMBER_INT(SELF, encode4_data_offset) = 0;
}

// implementation for tick function (relevant only for UGens)
CK_DLL_TICKF(encode4_tickf)
{
    // get our c++ class pointer
    Encode4* encode_obj = (Encode4*)OBJ_MEMBER_INT(SELF, encode4_data_offset);

    // invoke our tick function; store in the magical out variable
    if (encode_obj)
    {
        encode_obj->tick(in, out, nframes);
    }
    // yes
    return TRUE;
}

CK_DLL_MFUN(encode4_geti)
{
    int index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode4* encode_obj = (Encode4*)OBJ_MEMBER_INT(SELF, encode4_data_offset);
    if (encode_obj) { RETURN->v_float = encode_obj->get_i(index); }
}

CK_DLL_MFUN(encode4_coefficients)
{
    // get our c++ class pointer
    Encode4* encode_obj = (Encode4*)OBJ_MEMBER_INT(SELF, encode4_data_offset);
    Chuck_ArrayFloat* coefficients = (Chuck_ArrayFloat*)GET_NEXT_OBJECT(ARGS);
    encode_obj->set_coefficients(coefficients, API);
}

CK_DLL_MFUN(encode4_get_chans)
{
    // get our c++ class pointer
    Encode4* encode_obj = (Encode4*)OBJ_MEMBER_INT(SELF, encode4_data_offset);
    RETURN->v_int = encode_obj->get_chans();
}

CK_DLL_MFUN(encode4_seti)
{
    float input_value = GET_NEXT_FLOAT(ARGS);
    int input_index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode4* encode_obj = (Encode4*)OBJ_MEMBER_INT(SELF, encode4_data_offset);
    if (encode_obj) { encode_obj->set_i(input_value, input_index); }
}

//=================================================//
// ************************************************//
//                                                 //   
// Encode5 DLL definitions ; Everett M. Carpenter  //
//                                                 //
// ************************************************//
//=================================================//
// implementation for the default constructor
CK_DLL_CTOR(encode5_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, encode5_data_offset) = 0;

    // instantiate our internal c++ class representation
    Encode5* encode_obj = new Encode5(API->vm->srate(VM));

    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, encode5_data_offset) = (t_CKINT)encode_obj;
}

// implementation for the destructor
CK_DLL_DTOR(encode5_dtor)
{
    // get our c++ class pointer
    Encode5* encode_obj = (Encode5*)OBJ_MEMBER_INT(SELF, encode5_data_offset);
    // clean up (this macro tests for NULL, deletes, and zeros out the variable)
    CK_SAFE_DELETE(encode_obj);
    // set the data field to 0
    OBJ_MEMBER_INT(SELF, encode5_data_offset) = 0;
}

// implementation for tick function (relevant only for UGens)
CK_DLL_TICKF(encode5_tickf)
{
    // get our c++ class pointer
    Encode5* encode_obj = (Encode5*)OBJ_MEMBER_INT(SELF, encode5_data_offset);

    // invoke our tick function; store in the magical out variable
    if (encode_obj)
    {
        encode_obj->tick(in, out, nframes);
    }
    // yes
    return TRUE;
}

CK_DLL_MFUN(encode5_geti)
{
    int index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode5* encode_obj = (Encode5*)OBJ_MEMBER_INT(SELF, encode5_data_offset);
    if (encode_obj) { RETURN->v_float = encode_obj->get_i(index); }
}

CK_DLL_MFUN(encode5_coefficients)
{
    // get our c++ class pointer
    Encode5* encode_obj = (Encode5*)OBJ_MEMBER_INT(SELF, encode5_data_offset);
    Chuck_ArrayFloat* coefficients = (Chuck_ArrayFloat*)GET_NEXT_OBJECT(ARGS);
    encode_obj->set_coefficients(coefficients, API);
}

CK_DLL_MFUN(encode5_get_chans)
{
    // get our c++ class pointer
    Encode5* encode_obj = (Encode5*)OBJ_MEMBER_INT(SELF, encode5_data_offset);
    RETURN->v_int = encode_obj->get_chans();
}

CK_DLL_MFUN(encode5_seti)
{
    float input_value = GET_NEXT_FLOAT(ARGS);
    int input_index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode5* encode_obj = (Encode5*)OBJ_MEMBER_INT(SELF, encode5_data_offset);
    if (encode_obj) { encode_obj->set_i(input_value, input_index); }
}

//=================================================//
