#pragma once

#include <string>
#include "Mobile.h"
#include "DateTime.h"


namespace LW1 
{
	namespace Models
	{
		struct Talk
		{
			private:
				Mobile mobile;
				DateTime callStart;
				DateTime callEnding;
				double talkTarification;

			public:
				// Constructors.
				Talk();
				Talk(const Mobile& mobile, const DateTime& callStart, const DateTime& callEnding, const double talkTarification);

				// Getters for Fields.
				Mobile getMobile() const;
				DateTime getCallStart() const;
				DateTime getCallEnding() const;
				double getTalkTarification() const;

				// Setters for Fields.
				void setMobile(const Mobile& newMobileVal);
				void setCallStart(const DateTime& newCallStartVal);
				void setCallEnding(const DateTime& newCallEndingVal);
				void setTalkTarification(const double& newTalkTarification);

				// Additional Functions.
				int getCallDuration() const;
				bool isCallAValidOne() const;
		};
	}
}
