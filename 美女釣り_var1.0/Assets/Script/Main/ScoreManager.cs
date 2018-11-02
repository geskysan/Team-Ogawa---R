using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreManager : MonoBehaviour {

    public int m_Score;
    [SerializeField] Text m_ScoreText;

	// Use this for initialization
	void Start () {
        m_Score = 0;
	}
	
	// Update is called once per frame
	void Update () {
        m_ScoreText.text = m_Score.ToString();
	}
}
