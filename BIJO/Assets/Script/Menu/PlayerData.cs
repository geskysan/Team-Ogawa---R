using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerData : MonoBehaviour {

    public string IDAddress = "153.126.208.136/player_data.php";

    [SerializeField] Text _playerName, _playerScore;

    public static int _myScore;
    private string _myName;

    private void Awake()
    {
        StartCoroutine("ID");
    }

    private void Update()
    {
        _playerName.text = _myName;
        _playerScore.text = _myScore.ToString();
    }

    IEnumerator ID()
    {
        Dictionary<string, string> dic = new Dictionary<string, string>();
        dic.Add("id", Catch.MyID.ToString());
        StartCoroutine(UserData(IDAddress,dic));
        yield return 0;
    }

    private IEnumerator UserData(string url,Dictionary<string,string> post)
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
            Debug.Log("取ってきたやーつ:" + www.text);

            string UserData = www.text;
            string[] Data = UserData.Split(',');
            _myName = Data[0];
            _myScore = int.Parse(Data[1]);

            Debug.Log(_myScore);
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
