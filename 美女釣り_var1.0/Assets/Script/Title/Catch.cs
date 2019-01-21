using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Catch : MonoBehaviour
{

    public static string UserName;  //PLAYER NAME
    public static int UserId;       //USER ID
    public static int HiScore;      //PLAYER HISCORE

    public string ServerAddress = "153.126.208.136/mysql_maxid.php";        //USERID PHP(取得) 
    public string SendAddress = "153.126.208.136/mysql_newplayer.php";      //USERNAME PHP(送信) 
    public string IDAddress = "153.126.208.136/player_data.php";            //PLAYERDATA PHP(取得)
    public string id;   //Serverにidを送る用の変数

    public Text InputText_;     //USERNAME用
    public GameObject NameField;    //名前を登録する場所
    public GameObject SelectButton; //決定ボタン

    int Createuser;
    int MyID;   //IDの変数

    void Start()
    {
        StartCoroutine("Access");   //Access関数の呼び出し
        Createuser = PlayerPrefs.GetInt("CreateUser315");    //登録されているか取得する
        MyID = PlayerPrefs.GetInt("myId");  //"myId"に保存されている数を取得する
    }

    void Update()
    {
        MyID = PlayerPrefs.GetInt("myId");  //"myId"に保存されている数を取得する
        //デバッグ用
        if (Input.GetKeyDown(KeyCode.A))
        {
            Debug.Log(MyID);
        }

        //マウスがクリックされたとき
        if (Input.GetMouseButtonDown(0))
        {
            //ゼロなら
            if (Createuser == 0)
            {
                NameField.SetActive(true);      //表示する
                SelectButton.SetActive(true);   //表示する
            }
            if (Createuser == 1)
            {
                StartCoroutine("Id");       //Id関数の呼び出し
                SceneNavigator.Instance.Change("menu");   //"menu"Sceneへ移動
            }
        }
    }

    //ボタン押したとき
    public void Test_Button()
    {
        StartCoroutine("User");     //User関数の呼び出し
        StartCoroutine("Access");   //Access関数の呼び出し
        PlayerPrefs.SetInt("CreateUser315", 1);//引数に数を持たせる
        SceneNavigator.Instance.Change("menu");
    }

    //ユーザー登録
    private IEnumerator User()
    {
        Dictionary<string, string> dic = new Dictionary<string, string>();  //コンストラクタ
        dic.Add("name", InputText_.GetComponent<Text>().text); //インプットフィールドからnameの取得
        StartCoroutine(Post(SendAddress, dic)); //SendAddressに送信するコルーチンを実行
        PlayerPrefs.SetInt("myId", UserId);//引数にUserIdを持たせる
        yield return 0;

    }

    //ユーザーネームとハイスコア取得
    private IEnumerator Id()
    {
        Dictionary<string, string> dic = new Dictionary<string, string>();  //コンストラクタ
        id = (MyID).ToString();   //String型に変換して代入
        dic.Add("id", id);  //idを送信
        StartCoroutine(UserData(IDAddress, dic)); //SendAddressに送信するコルーチンを実行
        yield return 0;
    }

    //MAX_IDを取得
    private IEnumerator Access()
    {
        Dictionary<string, string> dic = new Dictionary<string, string>();  //コンストラクタ
        StartCoroutine(Post(ServerAddress, dic));  //ServerAddress
        yield return 0;
    }

    //UserのMaxIdを取ってくる
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
        }
        else if (www.isDone)
        {
            UserId = int.Parse(www.text);   //取得したMAX_IDを変数に代入する
        }
    }

    private IEnumerator UserData(string url, Dictionary<string, string> post)
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
            UserName = Data[0];
            HiScore = int.Parse(Data[1]);
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
