/*                          =======================
============================   C/C++ HEADER FILE   ============================
                            =======================                       *//**
  NtpTimeSync.h

  Created by Onno Dirkzwager on 20.12.2020.
  Copyright (c) 2020 IOTAppStory. All rights reserved.

*///===========================================================================
#ifdef ESP8266
	#ifndef __NtpTimeSync_h__
		#define __NtpTimeSync_h__
			
			/*---------------------------------------------------------------------------*/
			/*                            DEFINITIONS AND MACROS                         */
			/*---------------------------------------------------------------------------*/
			#define MAGICBYTE 85
			#define RTCMEMBEGIN 81
			#define SNTP_USE_STORED_UNTILL_SYNC false
			
			
			
			/*---------------------------------------------------------------------------*/
			/*                                    INCLUDES                               */
			/*---------------------------------------------------------------------------*/
			#include <Arduino.h>      // configTime()
			#include <TZ.h>           // This database is autogenerated from IANA timezone database https://www.iana.org/time-zones
			#include <coredecls.h>    // settimeofday_cb()
			#include <sys/time.h>     // struct timeval
			#include "../../config.h" // overwrite SNTP_USE_STORED_UNTILL_SYNC with the libary settings
			
			extern "C" {
			  #include "user_interface.h" // used by the RTC memory read/write functions
                                    // used for storing last timestamp in between boots untill Ntp sync has taken place
			}
			
			
			
			/*                          =======================
			============================   STRUCT DEFINITION   =============================
										=======================                        *//**
			  rtcMemDef.

			*//*=========================================================================*/
			typedef struct {
				uint8_t markerFlag;
				long int lastKnownTime;
			} RtcLastNtpSync __attribute__((aligned(4)));

			
			
			/*                          =======================
			============================   CLASS DEFINITION    ============================
										=======================
			*/
			class NtpTimeSync {
				public:
					void Settimeofday(long int timestamp);
					void ServerSetup(const char* tz, const char* server1, const char* server2 = nullptr, const char* server3 = nullptr);
					bool WaitForSync(int retries, const char* waitChar = nullptr);

				private:
					bool _timeSet = false;
			};
			
			
			/*---------------------------------------------------------------------------*/
			/*                                    EOF                                    */
			/*---------------------------------------------------------------------------*/
		#endif // __NtpTimeSync_h__
#endif // ESP8266
