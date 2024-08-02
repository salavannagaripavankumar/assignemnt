
#include <iostream>
#include <string>
 
class SMF {
public:
    void createSession(const std::string& sessionId) {
        std::cout << "SMF: Creating session with ID: " << sessionId << std::endl;
    }
 
    void modifySession(const std::string& sessionId) {
        std::cout << "SMF: Modifying session with ID: " << sessionId << std::endl;
    }
 
    void deleteSession(const std::string& sessionId) {
        std::cout << "SMF: Deleting session with ID: " << sessionId << std::endl;
    }
};
 
class AMF {
private:
    SMF& smf;  // Reference to SMF
 
public:
    AMF(SMF& smf) : smf(smf) {}
 
    void registerUser(const std::string& userId) {
        std::cout << "AMF: Registering user with ID: " << userId << std::endl;
        smf.createSession("session_" + userId);
    }
 
    void modifyUserSession(const std::string& userId) {
        std::cout << "AMF: Modifying session for user with ID: " << userId << std::endl;
        smf.modifySession("session_" + userId);
    }
 
    void deregisterUser(const std::string& userId) {
        std::cout << "AMF: Deregistering user with ID: " << userId << std::endl;
        smf.deleteSession("session_" + userId);
    }
};
 
int main() {
    SMF smf;
    AMF amf(smf);
 
    std::string userId = "user123";
 
    amf.registerUser(userId);
    amf.modifyUserSession(userId);
    amf.deregisterUser(userId);
 
    return 0;
}