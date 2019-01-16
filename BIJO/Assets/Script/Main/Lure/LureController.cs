using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LureController : MonoBehaviour {

    [SerializeField] StartUpManager m_startUpManager;
    [SerializeField] float m_flickPower;

    // タップ座標
    private Vector2 m_tapPos, m_touchStartPos, m_touchEndPos;
    private float m_timeOut = 0.5f;

    // ルアーの初期位置
    private Vector3 m_StartPos;

    enum PLAYTYPE
    {
        Tap,
        Flick,
        TestTap,
        TestFlick
    };

    [SerializeField] PLAYTYPE m_playType;

    private void Start()
    {
        m_StartPos = this.gameObject.transform.position;
    }

    // Update is called once per frame
    void Update () {

        switch(m_playType)
        {
            case PLAYTYPE.Tap:
                if (m_startUpManager.m_OK)
                    Tap();
                break;

            case PLAYTYPE.Flick:
                if (m_startUpManager.m_OK)
                    Flick();
                break;

            case PLAYTYPE.TestTap:
                Tap();
                break;

            case PLAYTYPE.TestFlick:
                Flick();
                break;
        }
    }


    /// <summary>
    /// タップした位置に移動
    /// </summary>
    void Tap()
    {
        if(Input.GetMouseButtonDown(0))
        {
            // 非表示状態なら表示
            if(this.gameObject.activeSelf == false)
            {
                this.gameObject.SetActive(true);
            }

            // タップした位置
            m_tapPos = new Vector2(Input.mousePosition.x, Input.mousePosition.y);

            // Lureの位置をクリック地点に移動
            this.gameObject.transform.localPosition = new Vector3(m_tapPos.x - (Screen.width / 2), m_tapPos.y - (Screen.height / 2), 0f);
        }
    }

    /// <summary>
    /// フリックした座標の取得
    /// </summary>
    void  Flick()
    {
        var limitTime = 0f;

        if (Input.GetMouseButtonDown(0))
        {
            m_touchStartPos = new Vector3(Input.mousePosition.x,
                                          Input.mousePosition.y,
                                          Input.mousePosition.z);

            limitTime += Time.deltaTime * m_timeOut;
            Debug.Log(limitTime);
        }

        else if (Input.GetMouseButtonUp(0))
        {
            m_touchEndPos = new Vector3(Input.mousePosition.x,
                                        Input.mousePosition.y,
                                        Input.mousePosition.z);

            // 一定時間以内に指を離すとフリック判定
            if (limitTime < m_timeOut)
                GetDirection();
        }
    }

    /// <summary>
    /// フリックした方向を取得
    /// </summary>
    void GetDirection()
    {
        float directionX = m_touchEndPos.x - m_touchStartPos.x;
        float directionY = m_touchEndPos.y - m_touchStartPos.y;

        string Direction = "";

        if (Mathf.Abs(directionX) < Mathf.Abs(directionY))
        {
            if (10 > directionY)
            {
                // 下側にフリック
                Direction = "down";
            }
            else
            {
                this.gameObject.GetComponent<Rigidbody2D>().AddForce(new Vector2(directionX, directionY) * m_flickPower);
            }
        }

        else if(Mathf.Abs(directionY) < Mathf.Abs(directionX))
        {
            this.gameObject.GetComponent<Rigidbody2D>().AddForce(new Vector2(directionX, directionY) * m_flickPower);
        }

        else
        {
            // タッチを検出
            Direction = "touch";
        }

        // それぞれの方向の処理を入れる
        switch(Direction)
        {
            case "down":
                LureReset();
                Debug.Log("reset");
                break;

            case "touch":
                Debug.Log("touch");
                break;
        }

        SoundScript.Instance.PlaySE(SoundNameData.SE_FLICK);
    }

    public void LureReset()
    {
        this.gameObject.transform.position = m_StartPos;
        this.gameObject.GetComponent<Rigidbody2D>().velocity = Vector2.zero;
    }
}