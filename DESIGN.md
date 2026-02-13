# Rof - Design Document

## Vision
A deep, text-based simulation of a dystopic, vertical mega-city (Ecumenopolis). The game focuses on social simulation, emergent gameplay, and survival in a world that operates independently of the player.

## 1. The World (The Sprawl)
- **Structure:** 1000x1000 grid per level. Multiple Z-levels (Underbelly, Slums, Industrial, Residential, Corporate, Spire).
- **Architecture:** Dense urban environment. Very few "natural" caves. Layouts are city blocks, apartments, skyways, and maintenance tunnels.
- **Vibe:** "Coruscant meets Cyberpunk 2077." High tech, low life. Massive logistics networks transporting goods and people.

## 2. Entities & Simulation
- **Population:** ~10,000 active entities.
- **AI Model:** Needs-based AI (GOAP or Utility AI).
    - **Needs:** Hunger, Energy (Sleep), Social, Money.
    - **Schedule:** NPCs have daily routines (Home -> Commute -> Work -> Eat -> Socialize -> Home).
- **Memory:** NPCs remember interactions (Player stole from me -> Negative Rep).

## 3. Player Loop
- **Survival:** Maintain hunger/hydration (non-tedious, strategic resource management).
- **Economy:** Money (Credits) is king. Used for food, gear, rent, and bribes.
- **Progression:**
    - **Reputation:** The primary "leveling" metric. Unlocks better gigs and access to restricted Z-levels.
    - **Cybernetics/Gear:** Vertical progression in power/utility.
- **Activities:** Procedural Gigs (Delivery, Assassination, Espionage, Hacking, Protection).

## 4. Technical Architecture
- **Engine:** Custom C++ ECS (EnTT).
- **Input:** Turn-based, non-blocking (0% CPU idle).
- **Rendering:** ASCII/Unicode on Terminal (potentially using specialized glyphs for UI).
- **Optimization:** 
    - Spatial Partitioning (Grid/Quadtree) for queries.
    - "Reality Bubble": High-fidelity simulation near player, abstracted simulation (statistical) for distant entities.
    - **Background Computation:** Utilize "down time" between player turns to pre-compute heavy NPC logic (pathfinding, schedule updates) to ensure smooth gameplay.

## 5. Roadmap
1.  **Foundation:** ECS, Map 1000x1000, Rendering, Basic Movement. [CURRENT STATUS]
2.  **World Gen:** FastNoise-based city layout (Streets vs Buildings).
3.  **Navigation:** Pathfinding (A* / Dijkstra) for NPCs in a city maze.
4.  **Simulation v1:** Basic NPC movement and "Wandering" AI.
5.  **Simulation v2:** Needs (Hunger) and rudimentary Jobs.
6.  **Economy:** Credits, Vendors, and Item interaction.
7.  **Gigs & Rep:** The Mission system.
