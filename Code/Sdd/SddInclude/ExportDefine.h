#pragma once

#  if defined( _SDD_DLL )
#    define SDD_EXPORT   __declspec(dllexport)
#  else
#    define SDD_EXPORT   __declspec(dllimport)
#  endif