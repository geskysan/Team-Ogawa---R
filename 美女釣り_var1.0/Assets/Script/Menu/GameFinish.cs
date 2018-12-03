using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameFinish : MonoBehaviour
{

    void Start()
    {

    }

    void Update()
    {

    }

    public void GoFishing()
    {
        SceneNavigator.Instance.Change("main");
    }

    public void GoLure()
    {
        SceneNavigator.Instance.Change("menu-lure");
    }

    public void GoGacha()
    {
        SceneNavigator.Instance.Change("menu-gacha");
    }
}