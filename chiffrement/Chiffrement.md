# Projet Client-Serveur UDP avec Chiffrement César

## Description

Ce projet implémente une communication **UDP** entre un **serveur** et un **client**. Le serveur écoute les messages envoyés par le client, déchiffre ces messages, traite la demande et renvoie une réponse chiffrée. Le client chiffre ses messages avant de les envoyer au serveur, puis déchiffre la réponse reçue. Le chiffrement est effectué à l'aide de l'algorithme de **César**, où chaque caractère est décalé de 3 positions dans la table ASCII.

## Fonctionnalités

- **Serveur UDP** qui :
  - Écoute les messages envoyés par le client.
  - Déchiffre le message reçu.
  - Envoie une réponse chiffrée au client.
  
- **Client UDP** qui :
  - Chiffre son message avant de l'envoyer au serveur.
  - Déchiffre la réponse reçue du serveur.

- **Chiffrement César** (décalage de 3 caractères ASCII) utilisé pour chiffrer et déchiffrer les messages.

## Prérequis

- Un environnement **Linux** (Ubuntu recommandé).
- Le compilateur **GCC** installé pour compiler les fichiers C.

## Compilation et Exécution

### Étapes pour compiler et exécuter le programme :

1. **Cloner le projet ou télécharger les fichiers `serveur.c` et `client.c`**.

2. **Compiler les fichiers C :**

   Dans un terminal, exécute les commandes suivantes pour compiler le serveur et le client :

   ```bash
   gcc serveur.c -o serveur
   gcc client.c -o client

#### PASCAL Maxime