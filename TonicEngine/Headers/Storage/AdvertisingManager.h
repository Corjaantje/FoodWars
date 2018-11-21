#ifndef PROJECT_SWA_ADVERTISINGMANAGER_H
#define PROJECT_SWA_ADVERTISINGMANAGER_H

#include <string>
#include <vector>

class AdvertisingManager
{
public:
    std::string getCurrentAd() const;
    void setCurrentAd(const std::string& file) const;
    std::vector<std::string> getAdvertisements() const;
    ~AdvertisingManager();
    AdvertisingManager();
private:
    std::vector<std::string> _advertisements;
    void initializeAdvertisements(std::string path);

};
#endif //PROJECT_SWA_ADVERTISINGMANAGER_H
