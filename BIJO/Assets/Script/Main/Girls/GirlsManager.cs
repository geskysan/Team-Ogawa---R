using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GirlsManager : MonoBehaviour
{ 
    [SerializeField] ScoreManager scoreManager;

    [SerializeField] GameObject[] m_Girls, m_spawnPoint;
    [SerializeField, Header("最大数")] byte maxGirl;
    [SerializeField, Header("女の子の獲得スコア")] int[] m_girlScore;

    [SerializeField, Header("各女の子ゲット数")] public int[] m_GirlCount;

    [SerializeField] Text m_ComboText;
    float m_comboTime;
    int m_ComboCount;

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
    }

    /// <summary>
    /// 女の子たちの初回生成
    /// </summary>
    public void GirlsStartUp()
    {

        //// ランダムな方向に力を与える
        //float random_X, random_Y;
        //random_X = Random.Range(0f, 1f);
        //random_Y = Random.Range(0f, 1f);
        //var randomForce = new Vector2(random_X, random_Y);

        //this.gameObject.GetComponent<Rigidbody2D>().AddForce(randomForce, ForceMode2D.Force);

        //// ランダムな種類の美女生成
        //for (int i = 0; i < maxGirl; i++)
        //{
        //    var random = 0;
        //    random = Random.Range(0, m_Girls.Length);

        //    Instantiate(m_Girls[random]);
        //}

        // ランダムな種類の美女生成
        for (int i = 0; i < maxGirl; i++)
        {
            var random = 0;
            random = Random.Range(0, m_Girls.Length);

            Instantiate(m_Girls[random], m_spawnPoint[i].transform);
        }

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
        // コンボ持続中
        if (m_comboTime <= 3)
        {
            m_ComboCount++;
            Debug.Log("コンボ成功");
        }
        // コンボが途切れた
        else
        {
            m_comboTime = 0f;
            m_ComboCount = 0;
            Debug.Log("miss");
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