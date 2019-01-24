using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Ranking : MonoBehaviour {

    private string RankingAddress = "http://ik1-340-30132.vs.sakura.ne.jp/ranking.php";

    [SerializeField] Text[] _userNames;

    private string userName;

    private void Start()
    {
        StartCoroutine("Access");
    }

    private IEnumerator Access()
    {
        Dictionary<string, string> dic = new Dictionary<string, string>();
        StartCoroutine(Post(RankingAddress, dic));
        yield return 0;
    }

    private IEnumerator Post(string url,Dictionary<string,string> post)
    {
        WWWForm form = new WWWForm();

        foreach (KeyValuePair<string, string> post_arg in post)
        {
            form.AddField(post_arg.Key, post_arg.Value);
        }
        WWW www = new WWW(url, form);

        yield return StartCoroutine(CheckTimeOut(www, 3f)); //TimeOutSecond = 3s;

        if (www.error != null)
        {
            Debug.Log("HttpPost NG: " + www.error);
            //そもそも接続ができていないとき

        }
        else if (www.isDone)
        {
            Debug.Log(www.text);

            string UserData = www.text;
            for (int i = 0; i < 20; i++)
            {
                string[] Data = UserData.Split(',');
                _userNames[i].text = Data[i];
            }
        }
    }

    private IEnumerator CheckTimeOut(WWW www, float timeout)
    {
        float requestTime = Time.time;

        while (!www.isDone)
        {
            if (Time.time - requestTime < timeout)
                yield return null;
            else
            {
                Debug.Log("TimeOut");  //タイムアウト
                //タイムアウト処理
                //
                //
                break;
            }
        }
        yield return null;
    }

    private void Update()
    {
        if(Input.GetMouseButtonDown(0))
        {
            SceneNavigator.Instance.Change("menu");
        }
    }
}
