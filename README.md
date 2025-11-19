# Encode-Decode.chug
Ambisonic encoding and decoding chugins for ChucK

Currently functional:

      EncodeN // virtual source encoder & ambisonic panner
      SADN // sampling ambisonic decoder designed to receive speaker array angles
      DecodeN // sampling ambisonic decoder designed to receive speaker spherical harmonics
      BFormatN // gain UGen for BFormat signals (multi channel gain factor)
      ABFormat // convert AFromat to BFormat
      BAFormat // convert BFormat to AFormat

Coming soon:

      DBDN // dual band ambisonic decoding
      MMADN // mode matching ambisonic decoding

All UGens are capable of up to 5th order ambisonics, but can be compiled to 12th order if desired.
