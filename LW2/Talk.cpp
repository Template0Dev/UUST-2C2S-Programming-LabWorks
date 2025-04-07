#include "Talk.h"


namespace LW2
{
	namespace Models
	{
		Talk::Talk()
		{
			mobile = Mobile();
			callStart = DateTime();
			callEnding = DateTime();
			talkTarification = 100.00;
		}
		Talk::Talk(const Mobile& mobile, const DateTime& callStart, const DateTime& callEnding, const double talkTarification)
		{
			this->mobile = mobile;
			this->callStart = callStart;
			this->callEnding = callEnding;
			this->talkTarification = talkTarification;
		}

		Mobile Talk::getMobile() const { return mobile; }
		DateTime Talk::getCallStart() const { return callStart; }
		DateTime Talk::getCallEnding() const { return callEnding; }
		double Talk::getTalkTarification() const { return talkTarification; }

		void Talk::setMobile(const Mobile& newMobileValue) { mobile = newMobileValue; }
		void Talk::setCallStart(const DateTime& newCallStartVal) { callStart = newCallStartVal; }
		void Talk::setCallEnding(const DateTime& newCallEndingVal) { callEnding = newCallEndingVal; }
		void Talk::setTalkTarification(const double& newTalkTarification) { talkTarification = newTalkTarification; }

		int Talk::getCallDuration() const
		{
			time_t beginningUnixTime = getCallStart().toUnixTime();
			time_t endingUnixTime = getCallEnding().toUnixTime();

			return (int)(endingUnixTime - beginningUnixTime);
		}
		bool Talk::isCallAValidOne() const
		{
			time_t beginningUnixTime = getCallStart().toUnixTime();
			time_t endingUnixTime = getCallEnding().toUnixTime();

			return endingUnixTime - beginningUnixTime >= 0;
		}
	}
}
