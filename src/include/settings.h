#include <atomic>
#include <mutex>
#include <vector>
#include <string>

std::atomic<bool> g_show_window(false);
std::atomic<bool> g_running(true);
std::mutex g_message_mutex;
std::vector<std::string> g_messages;
std::string g_input_text;
std::string g_username = "User: " + std::to_string(rand() % 1000);
std::string g_server_ip = "127.0.0.1";
int g_server_port = 12345;
bool g_connected = false;