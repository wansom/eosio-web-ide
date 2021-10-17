// To see this in action, run this in a terminal:
//      gp preview $(gp url 8000)

import * as React from "react";
import * as ReactDOM from "react-dom";
import { Api, JsonRpc, RpcError } from "eosjs";
import { JsSignatureProvider } from "eosjs/dist/eosjs-jssig";

const rpc = new JsonRpc(""); // nodeos and web server are on same port

interface PostData {
  id?: number;
  user?: string;
  reply_to?: number;
  content?: string;
}
// enrollment data
interface enrollData {
  id?: number;
  user?: string;
  county?: string;
  nationalid?: number;
  constituency?: string;
  role?: string;
  ward?: string;
}
// voting data
interface VotingData {
  id?: number;
  user?: string;
  president?: string;
  governor?: string;
  womanrep?: string;
}

interface PostFormState {
  privateKey: string;
  data: PostData;
  error: string;
}
// enrollment form
interface EnrollFormState {
  privateKey: string;
  data: enrollData;
  error: string;
}
// voting from
interface VotingFormState {
  privateKey: string;
  data: VotingData;
  error: string;
}

class PostForm extends React.Component<{}, PostFormState> {
  api: Api;

  constructor(props: {}) {
    super(props);
    this.api = new Api({ rpc, signatureProvider: new JsSignatureProvider([]) });
    this.state = {
      privateKey: "5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3",
      data: {
        id: 0,
        user: "bob",
        reply_to: 0,
        content: "This is a test",
      },
      error: "",
    };
  }

  setData(data: PostData) {
    this.setState({ data: { ...this.state.data, ...data } });
  }

  async post() {
    try {
      this.api.signatureProvider = new JsSignatureProvider([
        this.state.privateKey,
      ]);
      const result = await this.api.transact(
        {
          actions: [
            {
              account: "talk",
              name: "post",
              authorization: [
                {
                  actor: this.state.data.user,
                  permission: "active",
                },
              ],
              data: this.state.data,
            },
          ],
        },
        {
          blocksBehind: 3,
          expireSeconds: 30,
        }
      );
      console.log(result);
      this.setState({ error: "" });
    } catch (e) {
      if (e.json) this.setState({ error: JSON.stringify(e.json, null, 4) });
      else this.setState({ error: "" + e });
    }
  }

  render() {
    return (
      <div>
        <table>
          <tbody>
            <tr>
              <td>Private Key</td>
              <td>
                <input
                  style={{ width: 500 }}
                  value={this.state.privateKey}
                  onChange={(e) =>
                    this.setState({ privateKey: e.target.value })
                  }
                />
              </td>
            </tr>
            <tr>
              <td>User</td>
              <td>
                <input
                  style={{ width: 500 }}
                  value={this.state.data.user}
                  onChange={(e) => this.setData({ user: e.target.value })}
                />
              </td>
            </tr>
            <tr>
              <td>Reply To</td>
              <td>
                <input
                  style={{ width: 500 }}
                  value={this.state.data.reply_to}
                  onChange={(e) => this.setData({ reply_to: +e.target.value })}
                />
              </td>
            </tr>
            <tr>
              <td>Content</td>
              <td>
                <input
                  style={{ width: 500 }}
                  value={this.state.data.content}
                  onChange={(e) => this.setData({ content: e.target.value })}
                />
              </td>
            </tr>
          </tbody>
        </table>
        <br />
        <button onClick={(e) => this.post()}>Post</button>
        {this.state.error && (
          <div>
            <br />
            Error:
            <code>
              <pre>{this.state.error}</pre>
            </code>
          </div>
        )}
      </div>
    );
  }
}
//voter enrollment form  component
class EnrollForm extends React.Component<{}, EnrollFormState> {
  api: Api;

  constructor(props: {}) {
    super(props);
    this.api = new Api({ rpc, signatureProvider: new JsSignatureProvider([]) });
    this.state = {
      privateKey: "5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3",
      data: {
        id: 0,
        user: "bob",
        county: "homabay",
        nationalid: 35274575,
        constituency: "homabay",
        role: "admin",
        ward: "homabay",
      },
      error: "",
    };
  }

  setData(data: enrollData) {
    this.setState({ data: { ...this.state.data, ...data } });
  }
  async post() {
    try {
      this.api.signatureProvider = new JsSignatureProvider([
        this.state.privateKey,
      ]);
      const result = await this.api.transact(
        {
          actions: [
            {
              account: "talk",
              name: "enroll",
              authorization: [
                {
                  actor: this.state.data.user,
                  permission: "active",
                },
              ],
              data: this.state.data,
            },
          ],
        },
        {
          blocksBehind: 3,
          expireSeconds: 30,
        }
      );
      console.log(result);
      this.setState({ error: "" });
    } catch (e) {
      if (e.json) this.setState({ error: JSON.stringify(e.json, null, 4) });
      else this.setState({ error: "" + e });
    }
  }

  render() {
    return (
      <div>
        <p>Registration Form</p>
        <table>
          <tbody>
            <tr>
              <td>Private Key</td>
              <td>
                <input
                  style={{ width: 500 }}
                  value={this.state.privateKey}
                  onChange={(e) =>
                    this.setState({ privateKey: e.target.value })
                  }
                />
              </td>
            </tr>
            <tr>
              <td>Username</td>
              <td>
                <input
                  style={{ width: 500 }}
                  value={this.state.data.user}
                  onChange={(e) => this.setData({ user: e.target.value })}
                />
              </td>
            </tr>
            <tr>
              <td>National ID</td>
              <td>
                <input
                  style={{ width: 500 }}
                  value={this.state.data.nationalid}
                  onChange={(e) => this.setData({ nationalid: +e.target.value })}
                />
              </td>
            </tr>
            <tr>
              <td>County</td>
              <td>
                <input
                  style={{ width: 500 }}
                  value={this.state.data.county}
                  onChange={(e) => this.setData({ county: e.target.value })}
                />
              </td>
            </tr>
            <tr>
              <td>Constituency</td>
              <td>
                <input
                  style={{ width: 500 }}
                  value={this.state.data.constituency}
                  onChange={(e) => this.setData({ constituency: e.target.value })}
                />
              </td>
            </tr>
            <tr>
              <td>Ward</td>
              <td>
                <input
                  style={{ width: 500 }}
                  value={this.state.data.ward}
                  onChange={(e) => this.setData({ ward: e.target.value })}
                />
              </td>
            </tr>
            <tr>
              <td>Role</td>
              <td>
                <input
                  style={{ width: 500 }}
                  value={this.state.data.role}
                  onChange={(e) => this.setData({ role: e.target.value })}
                />
              </td>
            </tr>
          </tbody>
        </table>
        <br />
        <button onClick={(e) => this.post()}>Register</button>
        {this.state.error && (
          <div>
            <br />
            Error:
            <code>
              <pre>{this.state.error}</pre>
            </code>
          </div>
        )}
      </div>
    );
  }
}
// voting form component
class VotingForm extends React.Component<{}, VotingFormState> {
  api: Api;

  constructor(props: {}) {
    super(props);
    this.api = new Api({ rpc, signatureProvider: new JsSignatureProvider([]) });
    this.state = {
      privateKey: "EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV",
      data: {
        id: 0,
        user: "bob",
       president: "Ruto",
        governor: "miguna",
        womanrep:"waiguru"
      },
      error: "",
    };
  }

  setData(data: VotingData) {
    this.setState({ data: { ...this.state.data, ...data } });
  }

  async post() {
    try {
      this.api.signatureProvider = new JsSignatureProvider([
        this.state.privateKey,
      ]);
      const result = await this.api.transact(
        {
          actions: [
            {
              account: "talk",
              name: "vote",
              authorization: [
                {
                  actor: this.state.data.user,
                  permission: "active",
                },
              ],
              data: this.state.data,
            },
          ],
        },
        {
          blocksBehind: 3,
          expireSeconds: 30,
        }
      );
      console.log(result);
      this.setState({ error: "" });
    } catch (e) {
      if (e.json) this.setState({ error: JSON.stringify(e.json, null, 4) });
      else this.setState({ error: "" + e });
    }
  }

  render() {
    return (
      <div>
        <p>Voting form</p>
        <br />

        <table>
          <tbody>
            <tr>
              <td>Private Key</td>
              <td>
                <input
                  style={{ width: 500 }}
                  value={this.state.privateKey}
                  onChange={(e) =>
                    this.setState({ privateKey: e.target.value })
                  }
                />
              </td>
            </tr>
            <tr>
              <td>Voter name</td>
              <td>
                <input
                  style={{ width: 500 }}
                  value={this.state.data.user}
                  onChange={(e) => this.setData({ user: e.target.value })}
                />
              </td>
            </tr>
          
            <tr>
              <td>President</td>
              <td>
                <input
                  style={{ width: 500 }}
                  value={this.state.data.president}
                  onChange={(e) => this.setData({ president: e.target.value })}
                />
              </td>
            </tr>
            <tr>
              <td>Governor</td>
              <td>
                <input
                  style={{ width: 500 }}
                  value={this.state.data.governor}
                  onChange={(e) => this.setData({ governor: e.target.value })}
                />
              </td>
            </tr>
            <tr>
              <td>Women Rep</td>
              <td>
                <input
                  style={{ width: 500 }}
                  value={this.state.data.womanrep}
                  onChange={(e) => this.setData({ womanrep: e.target.value })}
                />
              </td>
            </tr>
          </tbody>
        </table>
        <br />
        <button onClick={(e) => this.post()}>Vote</button>
        {this.state.error && (
          <div>
            <br />
            Error:
            <code>
              <pre>{this.state.error}</pre>
            </code>
          </div>
        )}
      </div>
    );
  }
}


class Messages extends React.Component<{}, { content: string }> {
  interval: number;

  constructor(props: {}) {
    super(props);
    this.state = { content: "///" };
  }

  componentDidMount() {
    this.interval = window.setInterval(async () => {
      try {
        const rows = await rpc.get_table_rows({
          json: true,
          code: "talk",
          scope: "",
          table: "voters",
          limit: 1000,
        });
        let content =
          "id         username    county    constituenty   ward   role\n" +
          "=============================================================\n";
        for (let row of rows.rows)
          content +=
            (row.id + "").padEnd(12) +
            (row.user + "").padEnd(8) +
            "  " +
            row.county.padEnd(12) +
            row.constituency.padEnd(12) +
            row.ward.padEnd(10) +
            row.role +
            "\n";
        this.setState({ content });
      } catch (e) {
        if (e.json) this.setState({ content: JSON.stringify(e.json, null, 4) });
        else this.setState({ content: "" + e });
      }
    }, 200);
  }

  componentWillUnmount() {
    clearInterval(this.interval);
  }

  render() {
    return (
      <code>
        <pre>{this.state.content}</pre>
      </code>
    );
  }
}

ReactDOM.render(
  <div>
    
    <EnrollForm/>
    <br />
    <VotingForm/>
    <Messages/>
  </div>,
  document.getElementById("example")
);
