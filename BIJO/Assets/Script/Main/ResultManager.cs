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

    public string serverAddress = "153.126.208.136/newrecode.php";

    private void Awake()
    {
        //ハイスコアと比較して現在のスコアの方が上ならば送信する

        StartCoroutine(Access());
    }

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
		if(Input.GetMouseButtonDown(0))
        {
            SceneNavigator.Instance.Change("menu");
        }
	}

    IEnumerator Access()
    {
        Dictionary<string, int> dic = new Dictionary<string, int>();

        // phpにIDを送る(今はテストでID：１)
        dic.Add("id", 1);
        dic.Add("score", m_score);

        // phpにIDとスコアを送信
        StartCoroutine(Post(serverAddress, dic));

        yield return 0;
    }

    IEnumerator Post(string url,Dictionary<string,int> post)
    {
        WWWForm form = new WWWForm();

        foreach(KeyValuePair<string,int> post_arg in post)
        {
            form.AddField(post_arg.Key, post_arg.Value);
        }

        WWW www = new WWW(url, form);


        yield return StartCoroutine(CheckTimeOut(www, 3f));

        if(www.error != null)
        {
            Debug.Log("HttpPost NG: " + www.error);
        }
        else if(www.isDone)
        {
            Debug.Log("やり取り成功");
            Debug.Log(www.text);
        }
    }

    IEnumerator CheckTimeOut(WWW www, float timeout)
    {
        float requestTime = Time.time;

        while (!www.isDone)
        {
            if (Time.time - requestTime < timeout)
            {
                yield return null;
            }
            else
            {
                Debug.Log("TimeOut");
                //タイムアウト処理
                //
                //
                break;
            }
        }
        yield return null;
    }
}
