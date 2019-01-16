using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

public class ScoreManager : MonoBehaviour {

    public float m_Score;
    [SerializeField] Text m_ScoreText;

    [SerializeField] int maxCombo = 200;
    [SerializeField] float comboTime;

	// Use this for initialization
	void Start () {
        m_Score = 0;
	}
	
	// Update is called once per frame
	void Update () {
        m_ScoreText.text = m_Score.ToString("00");
	}

    /// <summary>
    /// スコアにコンボボーナスを付与
    /// </summary>
    /// <param name="Score">スコア数</param>
    /// <param name="comboCount">コンボ数</param>
    public void ScoreBonus(int Score, int comboCount)
    {
        var bonus = 1f;

        for (int i = 0; i <= maxCombo / 10; i++)
        {
            bonus += 0.2f;

            if (comboCount == i)
            {
                // コンボボーナスをプラスしたスコアを入れる
                m_Score += Score * bonus;
            }
        }
    }
}
