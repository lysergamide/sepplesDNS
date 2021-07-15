#include <DnsHeader.hpp>

/// @brief default constructor
DnsHeader::DnsHeader()
    : id { 0 }

    , recursion_desired { false }
    , truncated_message { false }
    , authoritative_answer { false }
    , opcode { 0 }
    , response { false }

    , rescode { ResultCode::NOERROR }
    , checking_disabled { false }
    , authed_data { false }
    , z { false }
    , recursion_available { false }

    , questions { 0 }
    , answers { 0 }
    , authoritative_entries { 0 }
    , resource_entries { 0 }
{
}

/// @brief make class printable
auto operator<<(std::ostream& os, const DnsHeader& h) -> std::ostream&
{
  // jfc

  os << "<DNS Header{\n"
     << "  recursion_desired: " << h.recursion_desired << "\n"
     << "  truncated_message: " << h.truncated_message << "\n"
     << "  authoritative_answer: " << h.authoritative_answer << "\n"
     << "  opcode: " << h.opcode << "\n"
     << "  response: " << h.response << "\n"
     << "  rescode: " << h.rescode << "\n"
     << "  checking_disabled: " << h.checking_disabled << "\n"
     << "  authed_data: " << h.authed_data << "\n"
     << "  z: " << h.z << "\n"
     << "  recursion_available: " << h.recursion_available << "\n"
     << "  questions: " << h.questions << "\n"
     << "  answers: " << h.answers << "\n"
     << "  authoritative_entries: " << h.authoritative_entries << "\n"
     << "  resource_entries: " << h.resource_entries << "\n}>";

  return os;
}