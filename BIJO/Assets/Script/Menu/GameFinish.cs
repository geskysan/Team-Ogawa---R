using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameFinish : MonoBehaviour
{

    [SerializeField]
    Sprite[] TutorialSS;

    [SerializeField]
    GameObject m_imagePanel, m_Tutorial;

    private int _tapCount;

    private void Start()
    {
        SoundScript.Instance.PlayBGM(SoundNameData.BGM_MENU);

        Debug.Log(Catch.UserName);

    }

    private void Update()
    {
        if(_tapCount == TutorialSS.Length)
        {
            m_Tutorial.SetActive(false);
        }
    }

    public void GoFishing()
    {
        SceneNavigator.Instance.Change("main");
    }

    public void GoCredit()
    {
        SceneNavigator.Instance.Change("credit");
    }

    public void GoTutorial()
    {
        _tapCount = 0;

        m_Tutorial.SetActive(true);
        m_imagePanel.GetComponent<Image>().sprite = TutorialSS[0];
    }

    public void NextButton()
    {
        _tapCount++;

        if (_tapCount != TutorialSS.Length)
            m_imagePanel.GetComponent<Image>().sprite = TutorialSS[_tapCount];
    }
}