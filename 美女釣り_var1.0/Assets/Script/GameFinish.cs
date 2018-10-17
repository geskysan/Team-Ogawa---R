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
        SceneManager.LoadScene("main");
    }

    public void GoLure()
    {
        SceneManager.LoadScene("menu-lure");
    }

    public void GoGacha()
    {
        SceneManager.LoadScene("menu-gacha");
    }
}