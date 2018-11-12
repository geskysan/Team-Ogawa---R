using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ResultManager : MonoBehaviour {

    [SerializeField] ScoreManager scoreManager;
    [SerializeField] GirlsManager girlsManager;

    [SerializeField] Text[] m_Text;
    [SerializeField] int[] m_girlsNum;
    int m_score;
    
	// Use this for initialization
	void Start () {
        // スコアを取得
        m_score = (int)scoreManager.m_Score;
        m_Text[0].text = m_score.ToString();
        
        for(int i=0;i<m_girlsNum.Length;i++)
        {
            // 女の子獲得数を取得
            m_girlsNum[i] = girlsManager.m_GirlCount[i];
            m_Text[i + 1].text = m_girlsNum[i].ToString();
        }
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
