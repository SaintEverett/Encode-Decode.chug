//-----------------------------------------------------------------------------
// Entaro ChucK Developer!
// This is a chugin boilerplate, generated by chuginate!
//-----------------------------------------------------------------------------
// NOTE by default, chuginate generates a new UGen subclass in this file
//      but it is possible, of course, to create non-UGen classes in a chugin!
// To modify this generated file for a non-UGen class...
//      1. in QUERY->begin_class(), change "UGen" to a different ChucK class
//         (e.g., `QUERY->begin_class(QUERY, "Decode", "Object");`)
//      2. remove or commment out the line containing QUERY->add_ugen_func()
//      3. that's it; the rest is no different for UGens/non-UGens
//-----------------------------------------------------------------------------
// 
//    matrix multi
// 
//                                           [w_0, w_1, w_2, w_3]
//                                           [y_0, y_1, y_2, y_3]
//         [w_in, y_in, x_in, z_in]     *    [x_0, x_1, x_2, x_3]  =  [w_out, y_out, x_out, z_out]
//                                           [z_0, z_1, z_2, z_3]
// 
//-----------------------------------------------------------------------------
// happy chucking & chugging!
//-----------------------------------------------------------------------------

// include chugin header
#include "chugin.h"  

// general includes
#include <iostream>
#include <thread>
#include <limits.h>
#include <math.h>

// declaration of chugin constructor
CK_DLL_CTOR(decode1_ctor);
CK_DLL_DTOR(decode1_dtor);
CK_DLL_TICKF(decode1_tickf);
CK_DLL_MFUN(decode1_set_coefficients);
// this is a special offset reserved for chugin internal data
t_CKINT decode1_data_offset = 0;

CK_DLL_CTOR(decode2_ctor);
CK_DLL_DTOR(decode2_dtor);
CK_DLL_TICKF(decode2_tickf);
CK_DLL_MFUN(decode2_set_coefficients);
// this is a special offset reserved for chugin internal data
t_CKINT decode2_data_offset = 0;

CK_DLL_CTOR(decode3_ctor);
CK_DLL_DTOR(decode3_dtor);
CK_DLL_TICKF(decode3_tickf);
CK_DLL_MFUN(decode3_set_coefficients);
// this is a special offset reserved for chugin internal data
t_CKINT decode3_data_offset = 0;

CK_DLL_CTOR(decode4_ctor);
CK_DLL_DTOR(decode4_dtor);
CK_DLL_TICKF(decode4_tickf);
CK_DLL_MFUN(decode4_set_coefficients);
// this is a special offset reserved for chugin internal data
t_CKINT decode4_data_offset = 0;

CK_DLL_CTOR(decode5_ctor);
CK_DLL_DTOR(decode5_dtor);
CK_DLL_TICKF(decode5_tickf);
CK_DLL_MFUN(decode5_set_coefficients);
// this is a special offset reserved for chugin internal data
t_CKINT decode5_data_offset = 0;


//-----------------------------------------------------------------------------
// class definition for internal chugin data
// (NOTE this isn't strictly necessary, but is one example of a recommended approach)
//-----------------------------------------------------------------------------
class DecodeN                                                                             
{                                                                                         
public:                                                                                   
    // constructor                                                                        
    DecodeN(t_CKFLOAT fs, t_CKUINT num_in, t_CKUINT num_out) :
        in_count(num_in), out_count(num_out)
    {
        coefficient_matrix = 0;
    }
    void multnsum(SAMPLE* in, SAMPLE* out)
    {
        for (int j = 0; j < in_count; j++)
        {
            for (int i = 0; i < in_count;i++)
            {
                out[j] += in[i] * coefficient_matrix[i][j];
            }
        }
    }
    void set_coefficients(CK_DL_API API, Chuck_ArrayInt* coefficients)
    {
        t_CKINT size_int = API->object->array_int_size(coefficients);
        t_CKUINT m = API->object->array_int_get_idx(coefficients, 0);
        Chuck_ArrayFloat* row = (Chuck_ArrayFloat*)m;
        t_CKINT size_float = API->object->array_float_size(row);
        if( size_int >= in_count)
        for (int i = 0; i < in_count; i++)
        {
            m = API->object->array_int_get_idx(coefficients, i);
            row = (Chuck_ArrayFloat*)m;
            if (size_float >= in_count)
            {
                for (int j = 0; j < in_count; j++)
                {
                    API->object->array_float_get_idx(row, j);
                }
            }
        }
    }
    void seti(CK_DL_API API, Chuck_ArrayFloat *coordinates, t_CKUINT entry)
    {
        int size = (API->object->array_float_size(coordinates));
        if (!entry > in_count) // if it isn't larger than in_count
        {
            if (!entry > size) // if it isn't larger than the given array
            {
                for (int i; i < size; i++)
                {
                    coefficient_matrix[i][entry] = API->object->array_float_get_idx(coordinates, i);
                }
            }
        } 
    }

protected:
    // instance data
    t_CKFLOAT** coefficient_matrix;
    t_CKUINT in_count = 0;
    t_CKUINT out_count = 0;
};


class Decode1 : public DecodeN
{
public:
    Decode1(t_CKFLOAT fs) : DecodeN(fs, 4, 4)
    {
        t_CKFLOAT coefficient_matrix[4][4] = { 0 };
    }
    
    // for chugins extending UGen
    SAMPLE tickf(SAMPLE* in, SAMPLE* out, int nframes)
    {
        // default: this passes whatever input is patched into chugin
        multnsum(in, out);
        return TRUE;
    }
};

class Decode2 : public DecodeN
{
public:
    Decode2(t_CKFLOAT fs) : DecodeN(fs, 9, 9)
    {
        t_CKFLOAT coefficient_matrix[9][9] = { 0 };
    }
    // for chugins extending UGen
    SAMPLE tickf(SAMPLE* in, SAMPLE* out, int nframes)
    {
        // default: this passes whatever input is patched into chugin
        multnsum(in, out);
        return TRUE;
    }
};

class Decode3 : public DecodeN
{
public:
    Decode3(t_CKFLOAT fs) : DecodeN(fs, 16, 16)
    {
        t_CKFLOAT coefficient_matrix[16][16] = { 0 };
    }
    // for chugins extending UGen
    SAMPLE tickf(SAMPLE* in, SAMPLE* out, int nframes)
    {
        // default: this passes whatever input is patched into chugin
        multnsum(in, out);
        return TRUE;
    }
};

class Decode4 : public DecodeN
{
public:
    Decode4(t_CKFLOAT fs) : DecodeN(fs, 25, 25)
    {
        t_CKFLOAT coefficient_matrix[25][25] = { 0 };
    }
    // for chugins extending UGen
    SAMPLE tickf(SAMPLE* in, SAMPLE* out, int nframes)
    {
        // default: this passes whatever input is patched into chugin
        multnsum(in, out);
        return TRUE;
    }
};

class Decode5 : public DecodeN
{
public:
    Decode5(t_CKFLOAT fs) : DecodeN(fs, 36, 36)
    {
        t_CKFLOAT coefficient_matrix[36][36] = { 0 };
    }
    // for chugins extending UGen
    SAMPLE tickf(SAMPLE* in, SAMPLE* out, int nframes)
    {
        // default: this passes whatever input is patched into chugin
        multnsum(in, out);
        return TRUE;
    }
};
//-----------------------------------------------------------------------------
// info function: ChucK calls this when loading/probing the chugin
// NOTE: please customize these info fields below; they will be used for
// chugins loading, probing, and package management and documentation
//-----------------------------------------------------------------------------
CK_DLL_INFO( Decode )
{
    // the version string of this chugin, e.g., "v1.2.1"
    QUERY->setinfo( QUERY, CHUGIN_INFO_CHUGIN_VERSION, "" );
    // the author(s) of this chugin, e.g., "Alice Baker & Carl Donut"
    QUERY->setinfo( QUERY, CHUGIN_INFO_AUTHORS, "" );
    // text description of this chugin; what is it? what does it do? who is it for?
    QUERY->setinfo( QUERY, CHUGIN_INFO_DESCRIPTION, "" );
    // (optional) URL of the homepage for this chugin
    QUERY->setinfo( QUERY, CHUGIN_INFO_URL, "" );
    // (optional) contact email
    QUERY->setinfo( QUERY, CHUGIN_INFO_EMAIL, "" );
}


//-----------------------------------------------------------------------------
// query function: ChucK calls this when loading the chugin
// modify this function to define this chugin's API and language extensions
//-----------------------------------------------------------------------------
CK_DLL_QUERY( Decode )
{
    // generally, don't change this...
    QUERY->setname( QUERY, "Decode" );

    // decode1
    QUERY->begin_class( QUERY, "Decode1", "UGen" );
    // register default constructor
    QUERY->add_ctor(QUERY, decode1_ctor);
    QUERY->add_dtor(QUERY, decode1_dtor);
    QUERY->add_mfun(QUERY, decode1_set_coefficients, "void", "set");
    // for UGens only: add tick function
    // NOTE a non-UGen class should remove or comment out this next line
    QUERY->add_ugen_funcf( QUERY, decode1_tickf, NULL, 4, 4 );
    // this reserves a variable in the ChucK internal class to store 
    // referene to the c++ class we defined above
    decode1_data_offset = QUERY->add_mvar( QUERY, "int", "@d_data", false );
    QUERY->end_class( QUERY );

    // decode2
    QUERY->begin_class(QUERY, "Decode2", "UGen");
    // register default constructor
    QUERY->add_ctor(QUERY, decode2_ctor);
    QUERY->add_dtor(QUERY, decode2_dtor);
    QUERY->add_mfun(QUERY, decode2_set_coefficients, "void", "set");
    // for UGens only: add tick function
    // NOTE a non-UGen class should remove or comment out this next line
    QUERY->add_ugen_funcf(QUERY, decode2_tickf, NULL, 9, 9);
    // this reserves a variable in the ChucK internal class to store 
    // referene to the c++ class we defined above
    decode2_data_offset = QUERY->add_mvar(QUERY, "int", "@d_data", false);
    QUERY->end_class(QUERY);

    // decode3
    QUERY->begin_class(QUERY, "Decode3", "UGen");
    // register default constructor
    QUERY->add_ctor(QUERY, decode3_ctor);
    QUERY->add_dtor(QUERY, decode3_dtor);
    QUERY->add_mfun(QUERY, decode3_set_coefficients, "void", "set");
    // for UGens only: add tick function
    // NOTE a non-UGen class should remove or comment out this next line
    QUERY->add_ugen_funcf(QUERY, decode3_tickf, NULL, 16, 16);
    // this reserves a variable in the ChucK internal class to store 
    // referene to the c++ class we defined above
    decode3_data_offset = QUERY->add_mvar(QUERY, "int", "@d_data", false);
    QUERY->end_class(QUERY);

    // decode4
    QUERY->begin_class(QUERY, "Decode4", "UGen");
    // register default constructor
    QUERY->add_ctor(QUERY, decode4_ctor);
    QUERY->add_dtor(QUERY, decode4_dtor);
    QUERY->add_mfun(QUERY, decode4_set_coefficients, "void", "set");
    // for UGens only: add tick function
    // NOTE a non-UGen class should remove or comment out this next line
    QUERY->add_ugen_funcf(QUERY, decode4_tickf, NULL, 25, 25);
    // this reserves a variable in the ChucK internal class to store 
    // referene to the c++ class we defined above
    decode4_data_offset = QUERY->add_mvar(QUERY, "int", "@d_data", false);
    QUERY->end_class(QUERY);

    // decode5
    QUERY->begin_class(QUERY, "Decode5", "UGen");
    // register default constructor
    QUERY->add_ctor(QUERY, decode5_ctor);
    QUERY->add_dtor(QUERY, decode5_dtor);
    QUERY->add_mfun(QUERY, decode5_set_coefficients, "void", "set");
    QUERY->add_arg(QUERY, "float[][]", "coordinates");
    // for UGens only: add tick function
    // NOTE a non-UGen class should remove or comment out this next line
    QUERY->add_ugen_funcf(QUERY, decode5_tickf, NULL, 36, 36);
    // this reserves a variable in the ChucK internal class to store 
    // referene to the c++ class we defined above
    decode5_data_offset = QUERY->add_mvar(QUERY, "int", "@d_data", false);
    QUERY->end_class(QUERY);


    // wasn't that a breeze?
    return TRUE;
}

//===============================================================================
// implementation for the default constructor
CK_DLL_CTOR( decode1_ctor )
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT( SELF, decode1_data_offset ) = 0;
    
    // instantiate our internal c++ class representation
    Decode1 * d_obj = new Decode1( API->vm->srate(VM) );
    
    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT( SELF, decode1_data_offset ) = (t_CKINT)d_obj;
}

// implementation for the destructor
CK_DLL_DTOR( decode1_dtor )
{
    // get our c++ class pointer
    Decode1 * d_obj = (Decode1 *)OBJ_MEMBER_INT( SELF, decode1_data_offset );
    // clean up (this macro tests for NULL, deletes, and zeros out the variable)
    CK_SAFE_DELETE( d_obj );
    // set the data field to 0
    OBJ_MEMBER_INT( SELF, decode1_data_offset ) = 0;
}

// implementation for tick function (relevant only for UGens)
CK_DLL_TICKF( decode1_tickf )
{
    // get our c++ class pointer
    Decode1 * d_obj = (Decode1 *)OBJ_MEMBER_INT(SELF, decode1_data_offset);
 
    // invoke our tick function; store in the magical out variable
    if( d_obj ) *out = d_obj->tickf( in, out, nframes );

    // yes
    return TRUE;
}

CK_DLL_MFUN(decode1_set_coefficients)
{
    Decode1* decode_obj = (Decode1*)OBJ_MEMBER_UINT(SELF, decode1_data_offset);
    Chuck_ArrayInt* speak_coefficients = (Chuck_ArrayInt*)GET_NEXT_OBJECT(ARGS);
    decode_obj->set_coefficients(API, speak_coefficients);
}
//===============================================================================
// implementation for the default constructor
CK_DLL_CTOR(decode2_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, decode2_data_offset) = 0;

    // instantiate our internal c++ class representation
    Decode2* d_obj = new Decode2(API->vm->srate(VM));

    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, decode2_data_offset) = (t_CKINT)d_obj;
}

// implementation for the destructor
CK_DLL_DTOR(decode2_dtor)
{
    // get our c++ class pointer
    Decode2* d_obj = (Decode2*)OBJ_MEMBER_INT(SELF, decode2_data_offset);
    // clean up (this macro tests for NULL, deletes, and zeros out the variable)
    CK_SAFE_DELETE(d_obj);
    // set the data field to 0
    OBJ_MEMBER_INT(SELF, decode2_data_offset) = 0;
}

// implementation for tick function (relevant only for UGens)
CK_DLL_TICKF(decode2_tickf)
{
    // get our c++ class pointer
    Decode2* d_obj = (Decode2*)OBJ_MEMBER_INT(SELF, decode2_data_offset);

    // invoke our tick function; store in the magical out variable
    if (d_obj) *out = d_obj->tickf(in, out, nframes);

    // yes
    return TRUE;
}

CK_DLL_MFUN(decode2_set_coefficients)
{
    Decode2* decode_obj = (Decode2*)OBJ_MEMBER_UINT(SELF, decode2_data_offset);
    Chuck_ArrayInt* speak_coefficients = (Chuck_ArrayInt*)GET_NEXT_OBJECT(ARGS);
    decode_obj->set_coefficients(API, speak_coefficients);
}
//===============================================================================
// implementation for the default constructor
CK_DLL_CTOR(decode3_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, decode3_data_offset) = 0;

    // instantiate our internal c++ class representation
    Decode3* d_obj = new Decode3(API->vm->srate(VM));

    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, decode3_data_offset) = (t_CKINT)d_obj;
}

// implementation for the destructor
CK_DLL_DTOR(decode3_dtor)
{
    // get our c++ class pointer
    Decode3* d_obj = (Decode3*)OBJ_MEMBER_INT(SELF, decode3_data_offset);
    // clean up (this macro tests for NULL, deletes, and zeros out the variable)
    CK_SAFE_DELETE(d_obj);
    // set the data field to 0
    OBJ_MEMBER_INT(SELF, decode3_data_offset) = 0;
}

// implementation for tick function (relevant only for UGens)
CK_DLL_TICKF(decode3_tickf)
{
    // get our c++ class pointer
    Decode3* d_obj = (Decode3*)OBJ_MEMBER_INT(SELF, decode3_data_offset);

    // invoke our tick function; store in the magical out variable
    if (d_obj) *out = d_obj->tickf(in, out, nframes);

    // yes
    return TRUE;
}

CK_DLL_MFUN(decode3_set_coefficients)
{
    Decode3* decode_obj = (Decode3*)OBJ_MEMBER_UINT(SELF, decode3_data_offset);
    Chuck_ArrayInt* speak_coefficients = (Chuck_ArrayInt*)GET_NEXT_OBJECT(ARGS);
    decode_obj->set_coefficients(API, speak_coefficients);
}
//===============================================================================
// implementation for the default constructor
CK_DLL_CTOR(decode4_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, decode4_data_offset) = 0;

    // instantiate our internal c++ class representation
    Decode4* d_obj = new Decode4(API->vm->srate(VM));

    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, decode4_data_offset) = (t_CKINT)d_obj;
}

// implementation for the destructor
CK_DLL_DTOR(decode4_dtor)
{
    // get our c++ class pointer
    Decode4* d_obj = (Decode4*)OBJ_MEMBER_INT(SELF, decode4_data_offset);
    // clean up (this macro tests for NULL, deletes, and zeros out the variable)
    CK_SAFE_DELETE(d_obj);
    // set the data field to 0
    OBJ_MEMBER_INT(SELF, decode4_data_offset) = 0;
}

// implementation for tick function (relevant only for UGens)
CK_DLL_TICKF(decode4_tickf)
{
    // get our c++ class pointer
    Decode4* d_obj = (Decode4*)OBJ_MEMBER_INT(SELF, decode4_data_offset);

    // invoke our tick function; store in the magical out variable
    if (d_obj) *out = d_obj->tickf(in, out, nframes);

    // yes
    return TRUE;
}

CK_DLL_MFUN(decode4_set_coefficients)
{
    Decode4* decode_obj = (Decode4*)OBJ_MEMBER_UINT(SELF, decode4_data_offset);
    Chuck_ArrayInt* speak_coefficients = (Chuck_ArrayInt*)GET_NEXT_OBJECT(ARGS);
    decode_obj->set_coefficients(API, speak_coefficients);
}
//===============================================================================
// implementation for the default constructor
CK_DLL_CTOR(decode5_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, decode5_data_offset) = 0;

    // instantiate our internal c++ class representation
    Decode5* d_obj = new Decode5(API->vm->srate(VM));

    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, decode5_data_offset) = (t_CKINT)d_obj;
}

// implementation for the destructor
CK_DLL_DTOR(decode5_dtor)
{
    // get our c++ class pointer
    Decode5* d_obj = (Decode5*)OBJ_MEMBER_INT(SELF, decode5_data_offset);
    // clean up (this macro tests for NULL, deletes, and zeros out the variable)
    CK_SAFE_DELETE(d_obj);
    // set the data field to 0
    OBJ_MEMBER_INT(SELF, decode5_data_offset) = 0;
}

// implementation for tick function (relevant only for UGens)
CK_DLL_TICKF(decode5_tickf)
{
    // get our c++ class pointer
    Decode5* d_obj = (Decode5*)OBJ_MEMBER_INT(SELF, decode5_data_offset);

    // invoke our tick function; store in the magical out variable
    if (d_obj) *out = d_obj->tickf(in, out, nframes);

    // yes
    return TRUE;
}

CK_DLL_MFUN(decode5_set_coefficients)
{
    Decode5* decode_obj = (Decode5*)OBJ_MEMBER_UINT(SELF, decode5_data_offset);
    Chuck_ArrayInt* speak_coefficients = (Chuck_ArrayInt*)GET_NEXT_OBJECT(ARGS);
    decode_obj->set_coefficients(API, speak_coefficients);
}
//===============================================================================
