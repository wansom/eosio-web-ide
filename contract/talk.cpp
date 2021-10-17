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

    // voters new table
struct [[eosio::table("voters"), eosio::contract("talk")]] voters {
    uint64_t    id       = {}; // Non-0
    uint64_t    reply_to = {}; // Non-0 if this is a reply
    eosio::name user     = {};
    string county ={};
    int nationalid={};
    string constituency={};
    string ward={};
    string role={};

    uint64_t primary_key() const { return id; }
    uint64_t get_reply_to() const { return reply_to; }
};

using voters_table = eosio::multi_index<
    "voters"_n, voters, eosio::indexed_by<"by.reply.to"_n, eosio::const_mem_fun<voters, uint64_t, &voters::get_reply_to>>>;

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
    [[eosio::action]] void enroll(uint64_t id,eosio::name user, string county, int nationalid, string constituency, string role, string ward){
    
    // Create a record in the table if the voter does not exist.
     voters_table table{get_self(),0};
             // Create an ID if user didn't specify one
    eosio::check(id < 1'000'000'000ull, "user-specified id is too big");
    if (!id)
        id = std::max(table.available_primary_key(), 1'000'000'000ull);
     table.emplace(get_self(), [&](auto& voters) {
            voters.id  =id;
            voters.user = user;
            voters.county= county;
            voters.nationalid     = nationalid;
            voters.constituency  = constituency;
            voters.ward = ward;
            voters.role=role;
           

        });

    }
    // cast vote
    [[eosio::action]] void vote(uint64_t id,eosio::name user,string president, string governor, string womanrep){
    // Create a record in the table if the vote does not exist
     votes_table _votes{get_self(),0};

       // Check user
        require_auth(user);

        // Check reply_to exists
        if (id)
            _votes.get(id);
        _votes.emplace(get_self(), [&](auto& rows){
            rows.president = president;
            rows.governor = governor;
            rows.womanrep = womanrep;
        });
            
    }
    
 public:
     struct [[eosio::table]] users_struct
    {
    uint64_t    id       = {};

    string name;
    string county;
    int nationalid;
    string constituency;
    string ward;
    string role;
    uint16_t reward_points = 0;

    uint64_t primary_key() const { return id; }
     };

    typedef eosio::multi_index<"users"_n, users_struct> users_table;
//votes table
    struct [[eosio::table]] votes_struct
    {
    uint64_t    id       = {};
     eosio::name user     = {};
     string president;
     string womanrep;
     string governor;
   
    uint64_t primary_key() const { return id; }
     };

    typedef eosio::multi_index<"votes"_n, votes_struct> votes_table;

};
