//
// Created by isnob on 14/05/2020.
//

#ifndef LAB1_MESSAGESTORE_H
#define LAB1_MESSAGESTORE_H

#include <string>
#include "Message.h"
#include <optional>

class MessageStore {
    Message *messages;
    int dim; // dimensione corrente array TOTALE
    int n; // incremento memoria
    int countMsg; // numero di elementi validi
public:
    MessageStore(int n);
    ~MessageStore();
    void add(Message &m);

    // inserisce un nuovo messaggio o sovrascrive quello precedente
    //se ce n’è uno presente con lo stesso id
    std::optional<Message> get(long id);
    // restituisce un messaggio se presente
    bool remove(long id);
    // cancella un messaggio se presente
    std::tuple<int, int> stats();
    // restituisce il numero di messaggi validi e di elementi vuoti
    // ancora disponibili
    void compact();
    // compatta l’array (elimina le celle vuole e riporta l’array
    // alla dimensione multiplo di n minima in grado di contenere
    // tutte le celle
};

#endif //LAB1_MESSAGESTORE_H
