//
//  main.cpp
//  AG1_2
//
//  Created by Jaroslav Bažant on 18.12.17.
//  Copyright © 2017 DewDrops. All rights reserved.
//

#include <iostream>
#include <stdio.h>

using namespace std;

struct Uzel //struktura reprezentující plat
{
    long long plat;
    struct Uzel *levy_syn;
    struct Uzel *pravy_syn;
    long long vyska;
};

long long max(long long a, long long b){ //pomocná funkce vracející maximum ze dvou čísel
    return (a > b) ? a : b;
}

long long zjistiVysku(struct Uzel *u){
    if (u == NULL) {
        return 0;
    }
    return u->vyska;
}

long long zjistiVyvazeni(struct Uzel *u){
    if (u == NULL) {
        return 0;
    }
    return zjistiVysku(u->levy_syn) - zjistiVysku(u->pravy_syn);
}

struct Uzel* uzelSMinimalniHodnotou(struct Uzel *u){
    struct Uzel* soucasny_uzel = u;
    while (soucasny_uzel->levy_syn != NULL) {
        soucasny_uzel = soucasny_uzel->levy_syn;
    }
    return soucasny_uzel;
}

struct Uzel* novyUzel(long long hodnota){
    struct Uzel *u = new Uzel();
    u->plat = hodnota;
    u->levy_syn = NULL;
    u->pravy_syn = NULL;
    u->vyska = 1;
    return u;
}

struct Uzel* pravaRotace(struct Uzel *y){
    struct Uzel *x = y->levy_syn;
    struct Uzel *T2 = x->pravy_syn;
    x->pravy_syn = y;
    y->levy_syn = T2;
    y->vyska = max(zjistiVysku(y->levy_syn), zjistiVysku(y->pravy_syn)+1);
    x->vyska = max(zjistiVysku(x->levy_syn), zjistiVysku(x->pravy_syn)+1);
    return x;
}

struct Uzel* levaRotace(struct Uzel *x){
    struct Uzel *y = x->pravy_syn;
    struct Uzel *T2 = y->levy_syn;
    y->levy_syn = x;
    x->pravy_syn = T2;
    x->vyska = max(zjistiVysku(x->levy_syn), zjistiVysku(x->pravy_syn)+1);
    y->vyska = max(zjistiVysku(y->levy_syn), zjistiVysku(y->pravy_syn)+1);
    return  y;
}

struct Uzel* pridejUzel(struct Uzel *u, long long hodnota){
    if (u == NULL) {
        return novyUzel(hodnota);
    }
    
    if (hodnota < u->plat) {
        u->levy_syn = pridejUzel(u->levy_syn, hodnota);
    } else {
        u->pravy_syn = pridejUzel(u->pravy_syn, hodnota);
    }
    u->vyska = 1 + max(zjistiVysku(u->levy_syn), zjistiVysku(u->pravy_syn));
    long long balance = zjistiVyvazeni(u);
    if (balance > 1 && hodnota > u->levy_syn->plat){
        return pravaRotace(u);
    }
    if (balance < -1 && hodnota > u->pravy_syn->plat) {
        return levaRotace(u);
    }
    if (balance > 1 && hodnota > u->levy_syn->plat) {
        u->levy_syn = levaRotace(u->levy_syn);
        return pravaRotace(u);
    }
    if (balance < -1 && hodnota < u->pravy_syn->plat) {
        u->pravy_syn = pravaRotace(u->pravy_syn);
        return levaRotace(u);
    }
    return u;
}

struct Uzel* smazUzel(struct Uzel *u, long long hodnota){
    if (u == NULL) {
        return u;
    }
    if (hodnota < u->plat) {
        u->levy_syn = smazUzel(u->levy_syn, hodnota);
    } else if (hodnota > u->plat) {
        u->pravy_syn = smazUzel(u->pravy_syn, hodnota);
    } else {
        if ((u->levy_syn == NULL) || (u->pravy_syn == NULL)) {
            struct Uzel *temp = u->levy_syn ? u->levy_syn : u->pravy_syn;
            if (temp == NULL) {
                temp = u;
                u = NULL;
            } else {
                *u = *temp;
                delete temp;
            }
        } else {
            struct Uzel *temp = uzelSMinimalniHodnotou(u->pravy_syn);
            u->plat = temp->plat;
            u->pravy_syn = smazUzel(u->pravy_syn, temp->plat);
        }
    }
    if (u == NULL) {
        return u;
    }
    u->vyska = 1 + max(zjistiVysku(u->levy_syn), zjistiVysku(u->pravy_syn));
    long long balance = zjistiVyvazeni(u);
    
    if (balance > 1 && zjistiVyvazeni(u->levy_syn) >= 0) {
        return pravaRotace(u);
    }
    if (balance > 1 && zjistiVyvazeni(u->levy_syn) < 0) {
        u->levy_syn = levaRotace(u->levy_syn);
        return pravaRotace(u);
    }
    if (balance < -1 && zjistiVyvazeni(u->pravy_syn) <= 0) {
        return levaRotace(u);
    }
    if (balance < -1 && zjistiVyvazeni(u->pravy_syn) > 0) {
        u->pravy_syn = pravaRotace(u->pravy_syn);
        return levaRotace(u);
    }
    return u;
}

void preOrderPruchod(struct Uzel *root){
    if (root != NULL) {
        cout << root->plat;
        preOrderPruchod(root->levy_syn);
        preOrderPruchod(root->pravy_syn);
    }
}

void vypisMedian(long long min, long long max){
    //tady to projít, nalézt nejmenší hodnotu, od té to pak mastit někam do pole a udržovat si počet prvků v poli
    //pak pokud je počet lichý, vytisknout (pocet-1)/2 prvek
    //pokud je sudý počet, vytisknout pocet/2 prvek
    
    //teoreticky se dá projít celej strom preorder, pokud je hodnota v uzlu mezi vstupními hodnotami, tak jí tam přidat, pokud ne, tak ne
}

int main(int argc, const char * argv[]) {
    //nekonečná smyčka dokud vstup != 4
    //case vstup = 1 - pridej uzel
    //case vstup = 2 - smaz uzel
    //case vstup = 3 - spocti medián
    
}
