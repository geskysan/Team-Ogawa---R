using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InitPrefab : MonoBehaviour
{
    static SoundScript _soundScript;
    static SceneNavigator _sceneNavigator;
    static TapParticle _tapParticle;

    [RuntimeInitializeOnLoadMethod(RuntimeInitializeLoadType.BeforeSceneLoad)]
    private static void InitAudio()
    {
        var audioManager = Resources.Load("Prefab/AudioManager") as GameObject;
        Instantiate(audioManager);
        DontDestroyOnLoad(audioManager);
        _soundScript = audioManager.GetComponent<SoundScript>();
    }

    [RuntimeInitializeOnLoadMethod(RuntimeInitializeLoadType.BeforeSceneLoad)]
    private static void InitSceneChange()
    {
        var sceneNavigator = Resources.Load("Prefab/SceneNavigator") as GameObject;
        Instantiate(sceneNavigator);
        DontDestroyOnLoad(sceneNavigator);
        _sceneNavigator = sceneNavigator.GetComponent<SceneNavigator>();
    }
}