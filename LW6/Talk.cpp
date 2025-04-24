#include "Talk.h"
#include "Utils.h"
#include <iostream>
#include <fstream>


namespace LW6
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

        std::istream& operator >>(std::istream& in, Models::Talk& talk)
        {
            std::string name, surname, patronymic, phone;

            std::cout << "Имя: ";
            in >> name;

            std::cout << "Фамилия: ";
            in >> surname;

            std::cout << "Отчество: ";
            in >> patronymic;

            std::cout << "Телефон: ";
            in >> phone;

            Models::DateTime callStart, callEnding;
            for (int j = 0; j < 2;)
            {
                tm rawDateData {};
                std::cout << "Необходимо ввести дату (время) [hh MM ss dd mm yyyy] "
                    << (j == 0 ? "начала разговора" : "конца разговора") << ": ";

                while (!(in >> rawDateData.tm_hour >> rawDateData.tm_min >> rawDateData.tm_sec
                    >> rawDateData.tm_mday >> rawDateData.tm_mon >> rawDateData.tm_year))
                {
                    in.clear();
                    in.ignore(10000, '\n');
                }

                Models::DateTime dateTime(rawDateData.tm_sec, rawDateData.tm_min, rawDateData.tm_hour,
                    rawDateData.tm_mday, rawDateData.tm_mon, rawDateData.tm_year);

                if (!dateTime.isValidDate())
                {
                    std::cout << "Введённая дата некорректна. Необходимо повторить ввод." << std::endl;
                    continue;
                }

                if (j == 0)
                {
                    callStart = dateTime;
                    j++;
                }
                else
                {
                    if (dateTime <= callStart)
                    {
                        std::cout << "Тайминги разговора неверные. Введите данные (конец разговора) заново." << std::endl;
                    }
                    else
                    {
                        callEnding = dateTime;
                        j++;
                    }
                }
            }

            double talkTarification;
            std::cout << "Необходимо ввести тарификацию разговора (стоимость за минуту): ";
            while (!(in >> talkTarification))
            {
                in.clear();
                in.ignore(10000, '\n');
            }

            talk = Models::Talk(Models::Mobile(name, surname, patronymic, phone),
                callStart, callEnding, talkTarification);

            return in;
        }
        std::ifstream& operator >>(std::ifstream& in, Models::Talk& talk)
        {
            std::string line;
            if (!std::getline(in, line))
            {
                return in; // Return early if reading fails.
            }
            if (line.empty() || line.at(0) == '+') {
                return in;
            }

            std::string cells[8];
            int cellIndex = 0;
            size_t pos = 0;

            if (!line.empty() && line.at(0) == '|') {
                pos = 1;
            }

            while (cellIndex < 8)
            {
                size_t nextPos = line.find('|', pos);
                if (nextPos == std::string::npos)
                {
                    break;
                }
                std::string cell = line.substr(pos, nextPos - pos);
                cells[cellIndex] = trim(cell);
                cellIndex++;
                pos = nextPos + 1;
            }

            if (cellIndex < 8)
            {
                return in;
            }

            std::string name = cells[1];
            std::string surname = cells[2];
            std::string patronymic = cells[3];
            std::string phone = cells[4];
            std::string callStartStr = cells[5];
            std::string callEndingStr = cells[6];
            std::string callTarificationStr = cells[7];

            tm startStamp {}, endingStamp {};
            if (!Models::DateTime::tryParseDateTime(callStartStr.c_str(), startStamp) ||
                !Models::DateTime::tryParseDateTime(callEndingStr.c_str(), endingStamp))
            {
                return in;
            }

            Models::DateTime callStart(startStamp.tm_sec, startStamp.tm_min, startStamp.tm_hour,
                startStamp.tm_mday, startStamp.tm_mon, startStamp.tm_year);
            Models::DateTime callEnding(endingStamp.tm_sec, endingStamp.tm_min, endingStamp.tm_hour,
                endingStamp.tm_mday, endingStamp.tm_mon, endingStamp.tm_year);

            if (!callStart.isValidDate() || !callEnding.isValidDate() || (callEnding < callStart))
            {
                return in;
            }

            double talkTarification = 0.0;
            try
            {
                talkTarification = std::stod(callTarificationStr);
            }
            catch (const std::exception&)
            {
                return in;
            }

            talk = Models::Talk(Models::Mobile(name, surname, patronymic, phone),
                callStart, callEnding, talkTarification);

            return in;
        }
    }
}
