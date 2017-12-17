#ifndef CONFIGURATION_H
#define CONFIGURATION_H


class Configuration
{
private:
    map<string, string> m_CFG;

public:
    Configuration();
    ~Configuration();

    void ReadConfiguration(string file);
    bool exists(string key);
    int GetInt(string key, int defaultValue);
    string GetString(string key,string defaultValue);
    void Set(string key, string value);
};

#endif // CONFIGURATION_H
