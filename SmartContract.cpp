#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

// Transaction structure to log all transactions
struct Transaction {
    string from;
    string to;
    double amount;
    time_t timestamp;
    
    void display() const {
        cout << "From: " << from << " | To: " << to 
             << " | Amount: " << amount << " | Time: " 
             << put_time(localtime(&timestamp), "%Y-%m-%d %H:%M:%S") << endl;
    }
};

// Simple Smart Contract for a token/payment system
class SmartContract {
private:
    string contractOwner;
    map<string, double> balances;  // Account balances
    vector<Transaction> transactionHistory;
    double totalSupply;
    string contractName;
    bool contractPaused;
    
public:
    // Constructor - Initialize contract
    SmartContract(string owner, string name, double initialSupply) 
        : contractOwner(owner), contractName(name), 
          totalSupply(initialSupply), contractPaused(false) {
        balances[owner] = initialSupply;
        cout << "Contract '" << contractName << "' deployed by " << owner 
             << " with supply: " << initialSupply << endl;
    }
    
    // Modifier to check if caller is owner
    bool isOwner(string caller) const {
        return caller == contractOwner;
    }
    
    // Modifier to check if contract is not paused
    bool isActive() const {
        return !contractPaused;
    }
    
    // Get balance of an account
    double getBalance(string account) {
        if (balances.find(account) == balances.end()) {
            return 0;
        }
        return balances[account];
    }
    
    // Transfer tokens from sender to receiver
    bool transfer(string from, string to, double amount) {
        if (!isActive()) {
            cout << "Error: Contract is paused!" << endl;
            return false;
        }
        
        if (amount <= 0) {
            cout << "Error: Amount must be positive!" << endl;
            return false;
        }
        
        if (getBalance(from) < amount) {
            cout << "Error: Insufficient balance! Current: " << getBalance(from) << endl;
            return false;
        }
        
        // Execute transfer
        balances[from] -= amount;
        balances[to] += amount;
        
        // Log transaction
        Transaction txn = {from, to, amount, time(nullptr)};
        transactionHistory.push_back(txn);
        
        cout << "Transfer successful: " << amount << " tokens from " 
             << from << " to " << to << endl;
        return true;
    }
    
    // Mint new tokens (owner only)
    bool mint(string caller, string to, double amount) {
        if (!isOwner(caller)) {
            cout << "Error: Only contract owner can mint tokens!" << endl;
            return false;
        }
        
        if (amount <= 0) {
            cout << "Error: Amount must be positive!" << endl;
            return false;
        }
        
        balances[to] += amount;
        totalSupply += amount;
        
        cout << "Minted " << amount << " tokens to " << to << endl;
        return true;
    }
    
    // Burn tokens (remove from circulation)
    bool burn(string caller, double amount) {
        if (amount <= 0) {
            cout << "Error: Amount must be positive!" << endl;
            return false;
        }
        
        if (getBalance(caller) < amount) {
            cout << "Error: Insufficient balance to burn!" << endl;
            return false;
        }
        
        balances[caller] -= amount;
        totalSupply -= amount;
        
        cout << "Burned " << amount << " tokens from " << caller << endl;
        return true;
    }
    
    // Pause contract (owner only)
    bool pauseContract(string caller) {
        if (!isOwner(caller)) {
            cout << "Error: Only owner can pause the contract!" << endl;
            return false;
        }
        contractPaused = true;
        cout << "Contract paused!" << endl;
        return true;
    }
    
    // Resume contract (owner only)
    bool resumeContract(string caller) {
        if (!isOwner(caller)) {
            cout << "Error: Only owner can resume the contract!" << endl;
            return false;
        }
        contractPaused = false;
        cout << "Contract resumed!" << endl;
        return true;
    }
    
    // View all transaction history
    void viewTransactionHistory() {
        if (transactionHistory.empty()) {
            cout << "No transactions yet!" << endl;
            return;
        }
        
        cout << "\n=== Transaction History ===" << endl;
        for (size_t i = 0; i < transactionHistory.size(); i++) {
            cout << "[" << (i + 1) << "] ";
            transactionHistory[i].display();
        }
        cout << endl;
    }
    
    // Get contract info
    void getContractInfo() {
        cout << "\n=== Contract Info ===" << endl;
        cout << "Contract Name: " << contractName << endl;
        cout << "Owner: " << contractOwner << endl;
        cout << "Total Supply: " << totalSupply << endl;
        cout << "Active Accounts: " << balances.size() << endl;
        cout << "Contract Status: " << (contractPaused ? "PAUSED" : "ACTIVE") << endl;
        cout << endl;
    }
    
    // Get all account balances
    void getAllBalances() {
        cout << "\n=== Account Balances ===" << endl;
        for (auto& pair : balances) {
            cout << pair.first << ": " << pair.second << " tokens" << endl;
        }
        cout << endl;
    }
};

// Main function - Demo the smart contract
int main() {
    // Deploy smart contract
    SmartContract contract("Admin", "MyToken", 1000);
    contract.getContractInfo();
    
    // Create transactions
    cout << "\n--- Executing Transactions ---" << endl;
    contract.transfer("Admin", "Alice", 100);
    contract.transfer("Admin", "Bob", 50);
    contract.transfer("Alice", "Bob", 30);
    
    // Mint new tokens
    contract.mint("Admin", "Charlie", 75);
    
    // View balances
    contract.getAllBalances();
    
    // Burn tokens
    contract.burn("Bob", 20);
    
    // Pause contract
    contract.pauseContract("Admin");
    contract.transfer("Alice", "Bob", 10);  // Should fail - contract paused
    
    // Resume contract
    contract.resumeContract("Admin");
    contract.transfer("Alice", "Bob", 10);  // Should succeed
    
    // View transaction history
    contract.viewTransactionHistory();
    
    // Final contract info
    contract.getContractInfo();
    contract.getAllBalances();
    
    return 0;
}
