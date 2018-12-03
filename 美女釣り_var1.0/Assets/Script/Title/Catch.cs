using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Catch : MonoBehaviour
{

    public string ServerAddress = "153.126.208.136/mysql_maxid.php";
    public string SendAddress = "153.126.208.136/mysql_newplayer.php";

    public Text InputText_;     //idを入力するインプットフィールド

    //SendSignalボタンを押した時に実行されるメソッド
    //public void SendSignal_Button_Push()
    //{
    //    StartCoroutine("Access");   //Accessコルーチンの開始
    //}

    void Awake()
    {
        StartCoroutine("Access");
    }

    public void Test_Button()
    {
        StartCoroutine("test");
    }

    private IEnumerator test()
    {
        Dictionary<string, string> dic = new Dictionary<string, string>();

        dic.Add("name", InputText_.GetComponent<Text>().text);
        StartCoroutine(Post(SendAddress, dic));
        yield return 0;

    }

    private IEnumerator Access()
    {
        Dictionary<string, string> dic = new Dictionary<string, string>();

        StartCoroutine(Post(ServerAddress, dic));  // POST

        yield return 0;
    }

    private IEnumerator Post(string url, Dictionary<string, string> post)
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
            //送られてきたデータをテキストに反映
            Debug.Log("MaxNumber:" + www.text);
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
}
