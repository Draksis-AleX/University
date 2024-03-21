using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class GameData : ASave
{
    public string scene;

    public int arenaDefeated;
    public int nextScene;
    public bool tookPowerUp;
    public bool inMagazzino;
    public bool completedArena;
    public bool first_arena;
    public string run_start_date;
    public string run_start_time;
    public float run_time;
    public bool count_time;
    public int wavesCompleted;
    public bool CommandsArrow;
    public int wavesNumber;
    public int wave_enemies_number;

    public GameData() {

        arenaDefeated = 0;
        nextScene = 2;
        tookPowerUp = false;
        inMagazzino = false;
        completedArena = false;

        wavesNumber = 1;
        wave_enemies_number = 3;
        first_arena = true;
        wavesCompleted = 0;
        run_time = 0;
        count_time = false;

        scene = "StartScene";
    }
}
