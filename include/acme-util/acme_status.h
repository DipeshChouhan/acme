#ifndef ACME_UTIL_ERRORS_H
#define ACME_UTIL_ERRORS_H


typedef enum AcmeStatus{
  Decoder_FAIL,
  Decoder_SUCCESS,
  REAL_MODE,
  PROTECTED_MODE
} AcmeStatus;

#endif
