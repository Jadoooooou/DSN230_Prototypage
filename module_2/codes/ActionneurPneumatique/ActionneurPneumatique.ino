/*
  SEMAINE 3 - DIY SOFT ROBOTICS
  ESP32 + DRV8833 + pompe + valve 3 voies

  OBJECTIF :
  Gonfler → Tenir → Relâcher → Attendre → Répéter

  Le programme contrôle la circulation de l'air
  dans un actionneur pneumatique en PE.
*/


// ========================================
// 1. CONNEXIONS ÉLECTRONIQUES
// ========================================

// POMPE - canal A du DRV8833
const int POMPE_IN1 = 25;
const int POMPE_IN2 = 26;

// VALVE - canal B du DRV8833
const int VALVE_IN1 = 27;
const int VALVE_IN2 = 14;


// ========================================
// 2. DURÉES - À MODIFIER !
// ========================================

// Les durées sont en millisecondes.
// 1000 millisecondes = 1 seconde.

int dureeGonflage = 3000;     // 3 secondes
int dureeMaintien = 5000;     // 5 secondes
int dureeDegonflage = 5000;   // 5 secondes
int dureePause = 2000;        // 2 secondes


// ========================================
// 3. INITIALISATION
// ========================================

// setup() s'exécute une seule fois au démarrage.

void setup() {

  // Communication avec l'ordinateur
  Serial.begin(115200);

  // Configurer les broches comme sorties
  pinMode(POMPE_IN1, OUTPUT);
  pinMode(POMPE_IN2, OUTPUT);

  pinMode(VALVE_IN1, OUTPUT);
  pinMode(VALVE_IN2, OUTPUT);

  // Tout éteindre au démarrage
  digitalWrite(POMPE_IN1, LOW);
  digitalWrite(POMPE_IN2, LOW);
  digitalWrite(VALVE_IN1, LOW);
  digitalWrite(VALVE_IN2, LOW);

  // Le pin SLP du DRV8833 est relié au 3.3 V

  Serial.println("Systeme pneumatique pret !");

  delay(1000);
}


// ========================================
// 4. BOUCLE PRINCIPALE
// ========================================

// loop() se répète continuellement.

void loop() {

  gonfler();    // Phase 1
  tenir();      // Phase 2
  relacher();   // Phase 3
  attendre();   // Phase 4

}


// ========================================
// 5. CONTRÔLE DE LA POMPE
// ========================================

// Activer la pompe
void activerPompe() {
  digitalWrite(POMPE_IN1, HIGH);
  digitalWrite(POMPE_IN2, LOW);
}

// Arrêter la pompe
void arreterPompe() {
  digitalWrite(POMPE_IN1, LOW);
  digitalWrite(POMPE_IN2, LOW);
}


// ========================================
// 6. CONTRÔLE DE LA VALVE
// ========================================

// Activer la valve : air vers la chambre
void activerValve() {
  digitalWrite(VALVE_IN1, HIGH);
  digitalWrite(VALVE_IN2, LOW);
}

// Désactiver la valve : air vers l'échappement
void desactiverValve() {
  digitalWrite(VALVE_IN1, LOW);
  digitalWrite(VALVE_IN2, LOW);
}


// ========================================
// 7. LES QUATRE PHASES
// ========================================

// PHASE 1 - GONFLER
void gonfler() {

  Serial.println("GONFLER");

  activerValve();  // Dirige l'air vers la chambre
  activerPompe();  // Envoie de l'air

  delay(dureeGonflage);
}


// PHASE 2 - TENIR
void tenir() {

  Serial.println("TENIR");

  arreterPompe();  // Arrête la pompe
  activerValve();  // Garde l'échappement fermé

  delay(dureeMaintien);
}


// PHASE 3 - RELÂCHER
void relacher() {

  Serial.println("RELACHER");

  arreterPompe();     // Arrête la pompe
  desactiverValve();  // Ouvre l'échappement

  delay(dureeDegonflage);
}


// PHASE 4 - ATTENDRE
void attendre() {

  Serial.println("ATTENDRE");

  arreterPompe();
  desactiverValve();

  delay(dureePause);
}

