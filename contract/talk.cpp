#include <eosio/eosio.hpp>


using namespace eosio;
using namespace std;


// Message table
struct [[eosio::table("message"), eosio::contract("talk")]] message {
    uint64_t    id       = {}; // Non-0
    uint64_t    reply_to = {}; // Non-0 if this is a reply
    eosio::name user     = {};
    std::string content  = {};

    uint64_t primary_key() const { return id; }
    uint64_t get_reply_to() const { return reply_to; }
};

using message_table = eosio::multi_index<
    "message"_n, message, eosio::indexed_by<"by.reply.to"_n, eosio::const_mem_fun<message, uint64_t, &message::get_reply_to>>>;

// The contract
class talk : eosio::contract {
  public:
    // Use contract's constructor
    using contract::contract;

    // Post a message
    [[eosio::action]] void post(uint64_t id, uint64_t reply_to, eosio::name user, const std::string& content) {
        message_table table{get_self(), 0};

        // Check user
        require_auth(user);

        // Check reply_to exists
        if (reply_to)
            table.get(reply_to);

        // Create an ID if user didn't specify one
        eosio::check(id < 1'000'000'000ull, "user-specified id is too big");
        if (!id)
            id = std::max(table.available_primary_key(), 1'000'000'000ull);

        // Record the message
        table.emplace(get_self(), [&](auto& message) {
            message.id       = id;
            message.reply_to = reply_to;
            message.user     = user;
            message.content  = content;
        });
    }
    //add user
    // [[eosio::action]] void enroll(name user,name name, string county, string constituency,string ward, string role, string fingerprint, int nationalid){
    //         // Ensure this action is authorized by the player
    // // require_auth(user);

    // // Create a record in the table if the player doesn't exist in our app yet
    //  users_table _users{get_self(),0};
    //  _users.emplace(get_self(), [&](auto& rows) {
    //         rows.name      = name;
    //         rows.county= county;
    //         rows.nationalid     = nationalid;
    //         rows.constituency  = constituency;
    //     });

    // }
    
 private:
     struct [[eosio::table]] users_struct
    {
    name name;
    string county;
    int nationalid;
    string constituency;
    string ward;
    string role;
    string fingerprint;
    uint16_t reward_points = 0;

    uint64_t primary_key() const { return name.value; }
     };

    typedef eosio::multi_index<"users"_n, users_struct> users_table;

};
