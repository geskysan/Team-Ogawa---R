using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GirlsManager : MonoBehaviour
{ 
    [SerializeField] ScoreManager scoreManager;
    [SerializeField] StartUpManager startUpManager;

    [SerializeField] GameObject[] m_Girls, m_spawnPoint;
    [SerializeField, Header("女の子の獲得スコア")] int[] m_girlScore;

    [SerializeField, Header("各女の子ゲット数")] public int[] m_GirlCount;
    [SerializeField, Header("場にいる女の子")] List<GameObject> m_GirlsObj = new List<GameObject>();

    [SerializeField] Text m_ComboText;
    float m_comboTime;
    int m_ComboCount;

    public int m_girlsCount;

    // Use this for initialization
    void Start()
    {

    }

    private void Update()
    {
        // 10コンボ以上で文字色を変える
        if (m_ComboCount >= 10)
            m_ComboText.color = Color.red;
        
        else
            m_ComboText.color = Color.black;

        m_ComboText.text = m_ComboCount.ToString();

        m_comboTime += 1f * Time.deltaTime;

        // ３秒でコンボリセット
        if(m_comboTime > 3)
        {
            m_comboTime = 0f;
            m_ComboCount = 0;
        }


        if(startUpManager.m_OK)
        {
            // 場から６人以下になったら増やす
            while (m_girlsCount < 6)
            {
                GirlSpawn();
            }
        }
    }

    /// <summary>
    /// 女の子たちの初回生成
    /// </summary>
    public void GirlsStartUp()
    { 
        // ランダムな種類の美女生成
        for (int i = 0; i < m_spawnPoint.Length; i++)
        {
            var random = Random.Range(0, m_Girls.Length);

            Instantiate(m_Girls[random], m_spawnPoint[i].transform.position, Quaternion.identity);

            m_GirlsObj[i] = m_Girls[random];

            m_girlsCount++;
        }
    }

    /// <summary>
    /// 女の子ランダム生成
    /// </summary>
    public void GirlSpawn()
    {
        //**************************************************
        // タップモード
        //**************************************************

        //var random = 0;
        //random = Random.Range(0, m_Girls.Length);

        //Instantiate(m_Girls[random], this.gameObject.transform);


        //**************************************************
        // フリックモード
        //**************************************************
        var random = Random.Range(0, m_Girls.Length);
        var randamPosition = Random.Range(0, m_spawnPoint.Length);

        Instantiate(m_Girls[random], m_spawnPoint[randamPosition].transform.position, Quaternion.identity);
        m_GirlsObj[randamPosition] = m_Girls[random];

        m_girlsCount++;

    }

    /// <summary>
    /// ゲットした女の子の該当するスコアを獲得
    /// </summary>
    /// <param name="girlTag"></param>
    public void GirlCounter(string girlTag)
    {
        // コンボ持続中
        if (m_comboTime <= 3)
        {
            m_ComboCount++;
            Debug.Log("コンボ成功");
        }

        Debug.Log("コンボ数 : " + m_ComboCount);
        Debug.Log(m_comboTime);

        if (girlTag == "Girl01")
        {
            scoreManager.ScoreBonus(m_girlScore[0], m_ComboCount);
            m_GirlCount[0]++;
        }
        else if (girlTag == "Girl02")
        {
            scoreManager.ScoreBonus(m_girlScore[1], m_ComboCount);
            m_GirlCount[1]++;
        }
        else if (girlTag == "Girl03")
        {
            scoreManager.ScoreBonus(m_girlScore[2], m_ComboCount);
            m_GirlCount[2]++;
        }  
    }
}