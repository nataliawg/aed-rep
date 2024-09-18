#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <algorithm>
using namespace std;

class Solution {
private:

    //nodo para el chaining
    struct HashNode{

        string key;
        vector<string> value;
        HashNode* next;

        HashNode(string k, string v): key(k), next(nullptr){
            value.push_back(v);
        }
    };

    //funcion hash
    int hashFunction(const string& key, int table_size){

        int hash = 0;
        for (char c: key){
            hash = (hash * 31 + c) % table_size;
        }
        return hash;

    }
public:

    vector<vector<string>> groupAnagrams(vector<string>& strs){
        int table_size = 100;
        vector<HashNode*> hashTable(table_size, nullptr);

        //recorrer cada palabra y ordenarla
        for (const auto& word: strs){
            string sortedWord = word;
            sort(sortedWord.begin(), sortedWord.end());

            //sacar el indice para la palabra ordenada
            int hashIndex = hashFunction(sortedWord, table_size);

            //si hasta ahora no existia, se crea el nodo para ese indice
            if (hashTable[hashIndex] == nullptr){
                hashTable[hashIndex] == new HashNode(sortedWord, word);
            }

            else{
                HashNode* temp = hashTable[hashIndex];
                while (temp != nullptr){
                    if (temp->key == sortedWord){
                        temp->value.push_back(word);
                        break;
                    }
                    if (temp->next == nullptr){
                        temp->next = new HashNode(sortedWord, word);
                    }

                    temp = temp->next;
                }
            }

        }

        vector<vector<string>> result;
        for (int i = 0; i < table_size; ++i){
            HashNode* temp = hashTable[i];
            while (temp != nullptr){
                result.push_back(temp->value);
                temp = temp->next;
            }
        }

        return result;
    }

};
