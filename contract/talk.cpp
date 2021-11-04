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

    // users table
struct [[eosio::table("voters"), eosio::contract("talk")]] voters {
    uint64_t    id       = {}; // Non-0
    uint64_t    reply_to = {}; // Non-0 if this is a reply
    eosio::name user     = {};
    string dob ={};
    string username ={};
    string county ={};
    string constituency={};
    string ward={};
    string role={};

    uint64_t primary_key() const { return id; }
    uint64_t get_reply_to() const { return reply_to; }
};

using voters_table = eosio::multi_index<
    "voters"_n, voters, eosio::indexed_by<"by.reply.to"_n, eosio::const_mem_fun<voters, uint64_t, &voters::get_reply_to>>>;
        // candidates table
struct [[eosio::table("candidates"), eosio::contract("talk")]] candidates {
    uint64_t    id       = {}; // Non-0
    uint64_t    reply_to = {}; // Non-0 if this is a reply
    eosio::name user     = {};
    string dob ={};
    string username ={};
    string county ={};
    string constituency={};
    string ward={};
    string position={};

    uint64_t primary_key() const { return id; }
    uint64_t get_reply_to() const { return reply_to; }
};

using candidates_table = eosio::multi_index<
    "candidates"_n, candidates, eosio::indexed_by<"by.reply.to"_n, eosio::const_mem_fun<candidates, uint64_t, &candidates::get_reply_to>>>;
// votes table
struct [[eosio::table("votes"), eosio::contract("talk")]] votes {
    uint64_t    id       = {}; // Non-0
    uint64_t    reply_to = {}; // Non-0 if this is a reply
    eosio::name user     = {};
    string president ={};
     string womanrep ={};
     string governor ={};
     string mp ={};
     string mca={};
     string senator = {};
     string station = {};
     string total = {};

    uint64_t primary_key() const { return id; }
    uint64_t get_reply_to() const { return reply_to; }
};

using votes_table = eosio::multi_index<
    "votes"_n, votes, eosio::indexed_by<"by.reply.to"_n, eosio::const_mem_fun<votes, uint64_t, &votes::get_reply_to>>>;
// votes records 
struct [[eosio::table("records"), eosio::contract("talk")]] records {
    uint64_t    id       = {}; // Non-0
    uint64_t    reply_to = {}; // Non-0 if this is a reply
    eosio::name user     = {};
      string president ={};
     string womanrep ={};
     string governor ={};
     string mp ={};
     string mca={};
     string senator = {};
     string station = {};
     string total = {};

    uint64_t primary_key() const { return id; }
    uint64_t get_reply_to() const { return reply_to; }
};

using records_table = eosio::multi_index<
    "records"_n, records, eosio::indexed_by<"by.reply.to"_n, eosio::const_mem_fun<records, uint64_t, &records::get_reply_to>>>;
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
    [[eosio::action]] void enroll(uint64_t id,eosio::name user, string county, string dob,string username, string constituency, string role, string ward){
    
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
            voters.dob     = dob;
            voters.username = username;
            voters.constituency  = constituency;
            voters.ward = ward;
            voters.role=role;
           

        });

    }
        //add user
    [[eosio::action]] void addcandidate(uint64_t id,eosio::name user, string county, string dob,string username, string constituency, string position, string ward){
    
    // Create a record in the table if the voter does not exist.
     candidates_table table{get_self(),0};
             // Create an ID if user didn't specify one
    eosio::check(id < 1'000'000'000ull, "user-specified id is too big");
    if (!id)
        id = std::max(table.available_primary_key(), 1'000'000'000ull);
     table.emplace(get_self(), [&](auto& candidates) {
            candidates.id  =id;
            candidates.user = user;
            candidates.county= county;
            candidates.dob     = dob;
            candidates.username = username;
            candidates.constituency  = constituency;
            candidates.ward = ward;
            candidates.position=position;
           

        });

    }
    // cast vote
    [[eosio::action]] void vote(uint64_t id,eosio::name user,string president, string governor, string womanrep,string mp, string senator,string mca){
    // Create a record in the table if the vote does not exist
     records_table table{get_self(),0};

       // Check user
       // require_auth(user);
          // Create an ID if user didn't specify one
    eosio::check(id < 1'000'000'000ull, "user-specified id is too big");
    if (!id)
        id = std::max(table.available_primary_key(), 1'000'000'000ull);
     table.emplace(get_self(), [&](auto& votes) {
            votes.id  =id;
            votes.user = user;
            votes.president = president;
            votes.governor = governor;
            votes.womanrep = womanrep;
            votes.mp = mp;
            votes.senator = senator;
            votes.mca = mca;  

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

};
