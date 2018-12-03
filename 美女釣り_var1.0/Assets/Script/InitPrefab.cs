using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InitPrefab : MonoBehaviour
{
    static SoundScript soundScript;
    static SceneNavigator sceneNavigator;

    [RuntimeInitializeOnLoadMethod(RuntimeInitializeLoadType.BeforeSceneLoad)]
    private static void InitAudio()
    {
        var AudioManager = Resources.Load("Prefab/AudioManager") as GameObject;
        Instantiate(AudioManager);
        GameObject.DontDestroyOnLoad(AudioManager);
        soundScript = AudioManager.GetComponent<SoundScript>();
    }

    [RuntimeInitializeOnLoadMethod(RuntimeInitializeLoadType.BeforeSceneLoad)]
    private static void InitSceneChange()
    {
        var SceneNavigator = Resources.Load("Prefab/SceneNavigator") as GameObject;
        Instantiate(SceneNavigator);
        GameObject.DontDestroyOnLoad(SceneNavigator);
        sceneNavigator = SceneNavigator.GetComponent<SceneNavigator>();
    }
}