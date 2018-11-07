using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GirlsManager : MonoBehaviour
{ 
    [SerializeField] ScoreManager scoreManager;

    [SerializeField] GameObject[] m_Girls;
    [SerializeField, Header("最大数")] byte maxGirl;
    [SerializeField, Header("女の子の獲得スコア")] int[] m_girlScore;

    [SerializeField, Header("各女の子ゲット数")] int[] m_GirlCount;

    [SerializeField] float[] m_ComboBonus;
    [SerializeField] float comboBonus;
    float m_comboResetTime;
    int m_ComboCount;

    // Use this for initialization
    void Start()
    {
        // ランダムな方向に力を与える
        float random_X, random_Y;
        random_X = Random.Range(0f, 1f);
        random_Y = Random.Range(0f, 1f);
        var randomForce = new Vector2(random_X, random_Y);

        this.gameObject.GetComponent<Rigidbody2D>().AddForce(randomForce, ForceMode2D.Force);

        // ランダムな種類の美女生成
        for (int i = 0; i < maxGirl; i++)
        {
            var random = 0;
            random = Random.Range(0, m_Girls.Length);

            Instantiate(m_Girls[random]);
        }
    }

    private void Update()
    {
        m_comboResetTime += 1f * Time.deltaTime;
    }

    /// <summary>
    /// 女の子ランダム生成
    /// </summary>
    public void GirlSpawn()
    {
        var random = 0;

        random = Random.Range(0, m_Girls.Length);

        Instantiate(m_Girls[random], this.gameObject.transform);
    }

    /// <summary>
    /// ゲットした女の子の該当するスコアを獲得
    /// </summary>
    /// <param name="girlTag"></param>
    public void GirlCounter(string girlTag)
    {
        m_ComboCount++;

        Debug.Log("コンボ数 : " + m_ComboCount);
        Debug.Log(m_comboResetTime);

        // コンボが継続中なら
        if (m_comboResetTime < 0.5f)
        {
            comboBonus = m_ComboBonus[0];
        }

        if (girlTag == "Girl01")
        {
            scoreManager.m_Score += m_girlScore[0] * (int)comboBonus;
            m_GirlCount[0]++;
        }
        else if (girlTag == "Girl02")
        {
            scoreManager.m_Score += m_girlScore[1] * (int)comboBonus;
            m_GirlCount[1]++;
        }
        else if (girlTag == "Girl03")
        {
            scoreManager.m_Score += m_girlScore[2] * (int)comboBonus;
            m_GirlCount[2]++;
        }

        m_comboResetTime = 0f;       
    }
}