#ifndef API_CLIENT_H
#define API_CLIENT_H

#include "../telemetry/telemetry.h"

void network_begin();
bool api_send(const Telemetry* telemetry);

#endif // API_CLIENT_H
