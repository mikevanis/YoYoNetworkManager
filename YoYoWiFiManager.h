#ifndef YoYoWiFiManager_h
#define YoYoWiFiManager_h

#include "Arduino.h"

#include <ArduinoJson.h>
#include <DNSServer.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <WiFiMulti.h>

#include "CaptiveRequestHandler.h"
#include "YoYoWiFiManagerCredentials.h"

#include "Levenshtein.h"

#define SSID_MAX_LENGTH 31
#define WIFICONNECTTIMEOUT 60000

class YoYoWiFiManager
{
  private:
    YoYoWiFiManagerCredentials preferences;

    String wifiCredentials = "";
    String macCredentials = "";
    String myID = "";
    bool inList;

    uint8_t wifiLEDPin;

    enum PAIRED_STATUS {
      remoteSetup,
      localSetup,
      pairedSetup
    };
    static int currentPairedStatus;

    enum SETUP_STATUS {
      setup_pending,
      setup_client,
      setup_server,
      setup_finished
    };
    static int currentSetupStatus;

    const byte DNS_PORT = 53;
    DNSServer dnsServer;
    IPAddress apIP = IPAddress(192, 168, 4, 1);

    void listConnectedClients();

    bool disconnected = false;

    int getNumberOfMacAddresses();
    void addToMacAddressJSON(String addr);

    void setupCaptivePortal();

    //-----------------------------
    uint32_t wificheckMillis;
    uint32_t wifiCheckTime = 5000;

    WiFiMulti wifiMulti;

    String checkSsidForSpelling(String incomingSSID);
    bool isWifiValid(String incomingSSID);
    void printWifiStatus(uint8_t status);

  public:
    YoYoWiFiManager(uint8_t wifiLEDPin = 2);

    boolean autoConnect(char const *apName, char const *apPassword = NULL, bool forcePortal = false);

    void wifiCheck();
    void connectToWifi(String credentials);
    bool joinPeerNetwork(char const *apName, char const *apPassword);
    void createPeerNetwork(char const *apName, char const *apPassword);
    bool isConnected();
};

#endif