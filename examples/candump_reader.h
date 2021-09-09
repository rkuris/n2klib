#pragma once

void handleTemp(const n2k::Message &);
n2k::Packet & fromCandumpText(std::istream & s);

extern bool debugging;
